#ifndef TRABALHO_CHIP8_REGISTERS_H_
#define TRABALHO_CHIP8_REGISTERS_H_

#include <array>
#include <cstdint>

namespace trabalho {

class Registers {
	static constexpr auto COUNT = 16;

	std::array<uint8_t, COUNT> m_v;
	uint16_t m_program_counter;
	uint16_t m_index;

public:
	Registers();
	auto reset() -> void;

	auto v(uint8_t reg) -> uint8_t&;
	auto program_counter() -> uint16_t&;
	auto index() -> uint16_t&;
};

} // namespace trabalho

#endif // TRABALHO_CHIP8_REGISTERS_H_