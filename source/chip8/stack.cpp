#include "chip8/stack.h"

#include <iostream>
#include <stack>

namespace trabalho {

Stack::Stack() {
	reset();
}

auto Stack::reset() -> void {
	std::fill(m_stack.begin(), m_stack.end(), 0);
	m_count = 0;
}

auto Stack::pop() -> uint16_t {
	if (m_count == 0) {
		std::cerr << "Error: stack underflow" << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_stack[--m_count];
}

auto Stack::push(uint16_t value) -> void {
	if (m_count == SIZE) {
		std::cerr << "Error: stack overflow" << std::endl;
		exit(EXIT_FAILURE);
	}
	m_stack[m_count++] = value;
}

} // namespace trabalho