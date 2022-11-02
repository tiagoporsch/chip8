#ifndef TRABALHO_CHIP8_STACK_H_
#define TRABALHO_CHIP8_STACK_H_

#include <array>
#include <cstdint>

namespace trabalho {

class Stack {
	static constexpr auto SIZE = 12;

	std::array<uint16_t, 12> m_stack;
	uint8_t m_count;

public:
	Stack();
	auto reset() -> void;

	auto pop() -> uint16_t;
	auto push(uint16_t value) -> void;
};

}

#endif // TRABALHO_CHIP8_STACK_H_