#ifndef TRABALHO_CHIP8_KEYBOARD_H_
#define TRABALHO_CHIP8_KEYBOARD_H_

#include <array>
#include <cstdint>

namespace trabalho {

class Keyboard {
public:
	static constexpr auto KEY_COUNT = 16;
	static constexpr auto KEY_NONE = KEY_COUNT + 1;
	static constexpr auto KEY_WAIT = KEY_COUNT + 2;

private:
	std::array<bool, KEY_COUNT> m_key;
	uint8_t m_key_wait;

public:
	Keyboard();

	auto key(uint8_t key) -> bool;
	auto set_key(uint8_t key, bool pressed) -> void;
	auto last_key() -> uint8_t&;
};

} // namespace trabalho

#endif // TRABALHO_CHIP8_KEYBOARD_H_