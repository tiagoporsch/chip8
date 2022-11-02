#ifndef TRABALHO_CHIP8_EMULATOR_H_
#define TRABALHO_CHIP8_EMULATOR_H_

#include "cpu.h"
#include "keyboard.h"
#include "memory.h"
#include "screen.h"
#include "stack.h"
#include "timer.h"

namespace trabalho {

class Emulator {
protected:
	Memory m_memory;
	Screen m_screen;
	Stack m_stack;
	Registers m_registers;
	Keyboard m_keyboard;
	Timer m_delay_timer;
	Timer m_sound_timer;
	CPU m_cpu;

public:
	Emulator();
	virtual ~Emulator();

	auto reset() -> void;
	virtual auto run() -> void = 0;
};
	
} // namespace trabalho

#endif // TRABALHO_CHIP8_EMULATOR_H_