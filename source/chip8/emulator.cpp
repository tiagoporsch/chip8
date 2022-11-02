#include "chip8/emulator.h"

namespace trabalho {

Emulator::Emulator(): m_cpu {m_memory, m_screen, m_stack, m_registers, m_keyboard, m_delay_timer, m_sound_timer} {
}

Emulator::~Emulator() {
}

auto Emulator::reset() -> void {
	m_screen.clear();
	m_stack.reset();
	m_registers.reset();
	m_delay_timer.time() = 0;
	m_sound_timer.time() = 0;
}

} // namespace trabalho
