#include "chip8/memory.h"

#include <iomanip>

namespace trabalho {

Memory::Memory() {
	std::fill(m_memory.begin(), m_memory.end(), 0);
	std::copy(FONT.begin(), FONT.end(), m_memory.begin());
}

auto Memory::at(uint32_t address) -> uint8_t& {
	if (address >= SIZE) {
		std::cerr << "Error: invalid memory address 0x" << std::setw(4) << std::setfill('0') << std::hex << address << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_memory[address];
}

auto operator>>(std::istream& in, Memory& memory) -> std::istream& {
	for (uint16_t index = Memory::ROM_START; !in.eof(); index++) {
		auto c = in.get();
		if (c != EOF) {
			memory.at(index) = static_cast<uint8_t>(c);
		}
	}
	return in;
}

} // namespace trabalho