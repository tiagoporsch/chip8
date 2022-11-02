#ifndef TRABALHO_CHIP8_CPU_H_
#define TRABALHO_CHIP8_CPU_H_

#include <cstdint>
#include <random>

#include "keyboard.h"
#include "memory.h"
#include "registers.h"
#include "screen.h"
#include "stack.h"
#include "timer.h"

namespace trabalho {

class CPU {
	Memory& m_memory;
	Screen& m_screen;
	Stack& m_stack;
	Registers& m_registers;
	Keyboard& m_keyboard;
	Timer& m_delay_timer;
	Timer& m_sound_timer;

	std::random_device m_random_device;
	std::default_random_engine m_random_engine;

public:
	CPU(Memory& memory, Screen& screen, Stack& stack, Registers& registers, Keyboard& keyboard, Timer& delay_timer, Timer& sound_timer);

	auto cycle() -> void;
};

} // namespace trabalho

#endif // TRABALHO_CHIP8_CPU_H_