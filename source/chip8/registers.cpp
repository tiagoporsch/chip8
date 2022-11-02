#include "chip8/registers.h"

#include "chip8/memory.h"

namespace trabalho {

Registers::Registers() {
	reset();
}

auto Registers::reset() -> void {
	std::fill(m_v.begin(), m_v.end(), 0);
	m_program_counter = Memory::ROM_START;
	m_index = 0;
}

auto Registers::v(uint8_t reg) -> uint8_t& {
	if (reg >= COUNT) {
		std::cerr << "Error: invalid register " << std::hex << reg << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_v[reg];
}

auto Registers::program_counter() -> uint16_t& {
	return m_program_counter;
}

auto Registers::index() -> uint16_t& {
	return m_index;
}

} // namespace trabalho