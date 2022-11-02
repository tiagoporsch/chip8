#ifndef TRABALHO_CHIP8_SCREEN_H_
#define TRABALHO_CHIP8_SCREEN_H_

#include <array>
#include <cstdint>

namespace trabalho {

class Screen {
public:
	static constexpr auto WIDTH = 64;
	static constexpr auto HEIGHT = 32;

private:
	std::array<std::array<bool, HEIGHT>, WIDTH> m_pixels;

public:
	Screen();

	auto clear() -> void;
	auto at(uint8_t x, uint8_t y) -> bool&;
};

} // namespace trabalho

#endif // TRABALHO_CHIP8_SCREEN_H_