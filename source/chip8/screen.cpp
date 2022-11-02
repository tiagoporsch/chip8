#include "chip8/screen.h"

#include <iostream>

namespace trabalho {

Screen::Screen() {
	clear();
}

auto Screen::clear() -> void {
	for (auto& row : m_pixels) {
		std::fill(row.begin(), row.end(), false);
	}
}

auto Screen::at(uint8_t x, uint8_t y) -> bool& {
	if (x >= WIDTH || y >= HEIGHT) {
		std::cerr << "Error: invalid screen location " << std::to_string(x) << ", " << std::to_string(y) << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_pixels[x][y];
}

} // namespace trabalho