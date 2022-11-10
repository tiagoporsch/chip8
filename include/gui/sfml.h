#ifndef TRABALHO_GUI_SFML_H_
#define TRABALHO_GUI_SFML_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "chip8/emulator.h"

namespace trabalho {

class SfmlEmulator : public Emulator {
	enum class State {
		STOPPED,
		PAUSED,
		RUNNING,
	};

	static constexpr auto SCALE = 24;
	static constexpr auto STEPS_PER_CYCLE = 8;

	static constexpr std::array KEYMAP = {
		sf::Keyboard::Key::X,    sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2, sf::Keyboard::Key::Num3,
		sf::Keyboard::Key::Q,    sf::Keyboard::Key::W,    sf::Keyboard::Key::E,    sf::Keyboard::Key::A,
		sf::Keyboard::Key::S,    sf::Keyboard::Key::D,    sf::Keyboard::Key::Z,    sf::Keyboard::Key::C,
		sf::Keyboard::Key::Num4, sf::Keyboard::Key::R,    sf::Keyboard::Key::F,    sf::Keyboard::Key::V
	};

	static constexpr std::array GAME_LIST = {
		"15PUZZLE", "BLITZ", "BOWLING", "BREAKOUT", "BRIX", "CAVE",
		"CONNECT4", "DANGEROUS", "FILTER", "GUESS", "HIDDEN", "HI-LO",
		"KALEID", "MASTERMIND", "MAZE", "MERLIN", "MISSILE", "PADDLES",
		"PONG1", "PONG2", "PUZZLE", "SOCCER", "SQUASH", "SYZYGY", "TANK",
		"TETRIS", "TICTACTOE", "UFO", "VBRIX", "VERS", "WALL", "WIPEOFF",
		"WORM"
	};

	sf::RenderWindow m_window;
	sf::SoundBuffer m_beep_buffer;
	sf::Sound m_beep;

	State m_state;
	sf::Font m_font;
	std::array<sf::Text, GAME_LIST.size()> m_menu_items;

public:
	SfmlEmulator();

	auto run() -> void override;
};

} // namespace trabalho

#endif // TRABALHO_GUI_SFML_H_