#include "chip8/keyboard.h"

#include <algorithm>
#include <iostream>

namespace trabalho {

Keyboard::Keyboard() {
	std::fill(m_key.begin(), m_key.end(), false);
	m_key_wait = KEY_NONE;
}

auto Keyboard::key(uint8_t key) -> bool {
	if (key >= KEY_COUNT) {
		std::cerr << "Error: invalid key " << std::hex << key << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_key[key];
}

auto Keyboard::set_key(uint8_t key, bool pressed) -> void {
	if (key >= KEY_COUNT) {
		std::cerr << "Error: invalid key " << std::hex << key << std::endl;
		exit(EXIT_FAILURE);
	}
	if (pressed && m_key_wait == KEY_WAIT) {
		m_key_wait = key;
	}
	m_key[key] = pressed;
}

auto Keyboard::last_key() -> uint8_t& {
	return m_key_wait;
}

} // namespace trabalho