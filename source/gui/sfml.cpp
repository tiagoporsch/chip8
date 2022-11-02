#include "gui/sfml.h"

#include <fstream>

namespace trabalho {

SfmlEmulator::SfmlEmulator(): m_window {sf::VideoMode {Screen::WIDTH * SCALE, Screen::HEIGHT * SCALE}, "CHIP-8"} {
	m_window.setKeyRepeatEnabled(false);

	m_beep_buffer.loadFromFile("resources/beep.wav");
	m_beep.setBuffer(m_beep_buffer);
	m_beep.setLoop(true);

	m_state = State::STOPPED;
	m_font.loadFromFile("resources/OpenSans-Regular.ttf");

	float x = 4 * SCALE, y = 10 * SCALE;
	std::transform(GAME_LIST.begin(), GAME_LIST.end(), m_menu_items.begin(), m_menu_items.begin(), [this, &x, &y](const auto& game, auto& menu_item){
		menu_item.setFont(m_font);
		menu_item.setString(game);
		menu_item.setCharacterSize(1.5f * SCALE);
		menu_item.setFillColor({127, 127, 127});
		menu_item.setPosition({x, y});
		if ((y += 2 * SCALE) >= (Screen::HEIGHT - 8) * SCALE) {
			y = 10 * SCALE;
			x += 12 * SCALE;
		}
		return menu_item;
	});
}

auto SfmlEmulator::run() -> void {
	const sf::Time frame_delay = sf::seconds(1.0f / 60.0f); // 60 Hz
	sf::Clock clock;

	while (m_window.isOpen()) {
		clock.restart();

		sf::Event event;
		while (m_window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: {
					m_window.close();
					break;
				}
				case sf::Event::KeyPressed:
				case sf::Event::KeyReleased: {
					if (event.key.code == sf::Keyboard::Key::Escape && event.type == sf::Event::KeyReleased) {
						if (m_state == State::PAUSED) {
							m_state = State::RUNNING;
							if (m_beep.getStatus() == sf::Sound::Paused) {
								m_beep.play();
							}
						} else if (m_state == State::RUNNING) {
							m_state = State::PAUSED;
							if (m_beep.getStatus() == sf::Sound::Playing) {
								m_beep.pause();
							}
						}
					}
					auto key = std::find(KEYMAP.begin(), KEYMAP.end(), event.key.code);
					if (key != KEYMAP.end()) {
						m_keyboard.set_key(static_cast<uint8_t>(std::distance(KEYMAP.begin(), key)), event.type == sf::Event::KeyPressed);
					}
					break;
				}
				case sf::Event::MouseMoved: {
					if (m_state == State::RUNNING)
						break;
					auto mouse_position = static_cast<sf::Vector2f>(sf::Vector2i {
						event.mouseMove.x * (Screen::WIDTH * SCALE) / static_cast<int>(m_window.getSize().x),
						event.mouseMove.y * (Screen::HEIGHT * SCALE) / static_cast<int>(m_window.getSize().y)
					});
					for (auto& menu_item : m_menu_items) {
						if (menu_item.getGlobalBounds().contains(mouse_position)) {
							menu_item.setFillColor(sf::Color::White);
						} else {
							menu_item.setFillColor({127, 127, 127});
						}
					}
					break;
				}
				case sf::Event::MouseButtonReleased: {
					if (m_state == State::RUNNING || event.mouseButton.button != sf::Mouse::Button::Left)
						break;
					auto mouse_position = static_cast<sf::Vector2f>(sf::Vector2i {
						event.mouseButton.x * (Screen::WIDTH * SCALE) / static_cast<int>(m_window.getSize().x),
						event.mouseButton.y * (Screen::HEIGHT * SCALE) / static_cast<int>(m_window.getSize().y)
					});
					for (auto& menu_item : m_menu_items) {
						if (menu_item.getGlobalBounds().contains(mouse_position)) {
							std::ifstream rom {"resources/roms/" + menu_item.getString(), std::ios_base::openmode::_S_in};
							rom >> m_memory;
							rom.close();
							reset();
							m_state = State::RUNNING;
						}
					}
					break;
				}
				default:
					break;
			}
		}

		// Emulator cycle
		if (m_state == State::RUNNING) {
			m_delay_timer.tick();
			if (m_sound_timer.tick()) {
				m_beep.stop();
			}

			for (auto i = 0; i < STEPS_PER_CYCLE; i++) {
				m_cpu.cycle();
			}

			if (m_sound_timer.time() > 0 && m_beep.getStatus() != sf::Sound::Playing) {
				m_beep.play();
			}
		}

		// Render emulator screen
		m_window.clear(sf::Color {32, 32, 32});
		sf::RectangleShape pixel {{SCALE, SCALE}};
		pixel.setFillColor(sf::Color {224, 224, 224});
		for (uint8_t x = 0; x < Screen::WIDTH; x++) {
			for (uint8_t y = 0; y < Screen::HEIGHT; y++) {
				if (!m_screen.at(x, y))
					continue;
				pixel.setPosition(x * SCALE, y * SCALE);
				m_window.draw(pixel);
			}
		}

		// Render menu
		if (m_state != State::RUNNING) {
			pixel.setSize({Screen::WIDTH * SCALE, Screen::HEIGHT * SCALE});
			pixel.setPosition({0, 0});
			pixel.setFillColor({0, 0, 0, 192});
			m_window.draw(pixel);

			sf::Text text;
			text.setFont(m_font);
			text.setFillColor(sf::Color::White);
			text.setString("CHIP-8");
			text.setCharacterSize(4 * SCALE);
			text.setPosition({4 * SCALE, 4 * SCALE});
			m_window.draw(text);

			text.setString("(C) Tiago Porsch Dopke 2022");
			text.setCharacterSize(SCALE);
			text.setPosition({4 * SCALE, (Screen::HEIGHT - 6) * SCALE});
			m_window.draw(text);

			for (const auto& menu_item : m_menu_items) {
				m_window.draw(menu_item);
			}
		}

		// Update display and time loop
		m_window.display();
		auto frame_time = clock.getElapsedTime();
		if (frame_time < frame_delay) {
			sf::sleep(frame_delay - frame_time);
		}
	}
}

} // namespace trabalho