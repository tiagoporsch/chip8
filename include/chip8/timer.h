#ifndef TRABALHO_CHIP8_TIMER_H_
#define TRABALHO_CHIP8_TIMER_H_

#include <cstdint>

namespace trabalho {

class Timer {
	uint8_t m_time;

public:
	Timer();

	auto tick() -> bool;
	auto time() -> uint8_t&;
};

}

#endif // TRABALHO_CHIP8_TIMER_H_