#include "chip8/timer.h"

namespace trabalho {

Timer::Timer() {
	m_time = 0;
}

auto Timer::tick() -> bool {
	if (m_time > 0) {
		if (--m_time == 0) {
			return true;
		}
	}
	return false;
}

auto Timer::time() -> uint8_t& {
	return m_time;
}

} // namespace trabalho