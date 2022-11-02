#include "chip8/cpu.h"

#include <iomanip>

namespace trabalho {

CPU::CPU(Memory& memory, Screen& screen, Stack& stack, Registers& registers, Keyboard& keyboard, Timer& delay_timer, Timer& sound_timer):
m_memory {memory}, m_screen {screen}, m_stack {stack}, m_registers {registers}, m_keyboard {keyboard}, m_delay_timer {delay_timer}, m_sound_timer {sound_timer} {
}

auto CPU::cycle() -> void {
	uint16_t opcode = (m_memory.at(m_registers.program_counter()) << 8) | m_memory.at(m_registers.program_counter() + 1);

	uint16_t nnn = opcode & 0x0FFF; // address
	uint8_t nn = static_cast<uint8_t>(opcode & 0x00FF); // 8-bit constant
	uint8_t n = static_cast<uint8_t>(opcode & 0x000F); // 4-bit constant
	uint8_t x = static_cast<uint8_t>((opcode & 0x0F00) >> 8); // 4-bit register identifier
	uint8_t y = static_cast<uint8_t>((opcode & 0x00F0) >> 4); // 4-bit register identifier

	bool invalid = false;
	switch (opcode & 0xF000) {
		case 0x0000:
			switch (opcode & 0x00FF) {
				case 0x00E0: // clear
					m_screen.clear();
					m_registers.program_counter() += 2;
					break;
				case 0x00EE: // return
					m_registers.program_counter() = m_stack.pop();
					m_registers.program_counter() += 2;
					break;
				default:
					invalid = true;
					break;
			}
			break;
		case 0x1000: // goto NNN
			m_registers.program_counter() = nnn;
			break;
		case 0x2000: // call NNN
			m_stack.push(m_registers.program_counter());
			m_registers.program_counter() = nnn;
			break;
		case 0x3000: // skip next if Vx == NN
			if (m_registers.v(x) == nn)
				m_registers.program_counter() += 2;
			m_registers.program_counter() += 2;
			break;
		case 0x4000: // skip next if Vx != NN
			if (m_registers.v(x) != nn)
				m_registers.program_counter() += 2;
			m_registers.program_counter() += 2;
			break;
		case 0x5000: // skip next if Vx == Vy
			if (m_registers.v(x) == m_registers.v(y))
				m_registers.program_counter() += 2;
			m_registers.program_counter() += 2;
			break;
		case 0x6000: // Vx = NN
			m_registers.v(x) = nn;
			m_registers.program_counter() += 2;
			break;
		case 0x7000: // Vx += NN
			m_registers.v(x) += nn;
			m_registers.program_counter() += 2;
			break;
		case 0x8000:
			switch (opcode & 0x000F) {
				case 0x0000: // Vx = Vy
					m_registers.v(x) = m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0001: // Vx |= Vy
					m_registers.v(x) |= m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0002: // Vx &= Vy
					m_registers.v(x) &= m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0003: // Vx ^= Vy
					m_registers.v(x) ^= m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0004: // Vx += Vy (with carry)
					m_registers.v(0xF) = m_registers.v(x) + m_registers.v(y) > 0xFF ? 1 : 0;
					m_registers.v(x) += m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0005: // Vx -= Vy (with borrow)
					m_registers.v(0xF) = m_registers.v(x) >= m_registers.v(y) ? 1 : 0;
					m_registers.v(x) -= m_registers.v(y);
					m_registers.program_counter() += 2;
					break;
				case 0x0006: // Vx = Vy >> 1 (VF = LSB)
					m_registers.v(0xF) = m_registers.v(y) & 0x1;
					m_registers.v(x) = m_registers.v(y) >> 1;
					m_registers.program_counter() += 2;
					break;
				case 0x0007: // Vx = Vy - Vx (with borrow)
					m_registers.v(0xF) = m_registers.v(y) >= m_registers.v(x) ? 1 : 0;
					m_registers.v(x) = m_registers.v(y) - m_registers.v(x);
					m_registers.program_counter() += 2;
					break;
				case 0x000E: // Vx = Vy << 1 (VF = MSB)
					m_registers.v(0xF) = m_registers.v(y) >> 7;
					m_registers.v(x) = m_registers.v(y) << 1;
					m_registers.program_counter() += 2;
					break;
				default:
					invalid = true;
					break;
			}
			break;
		case 0x9000: // skip next if Vx != Vy
			if (m_registers.v(x) != m_registers.v(y))
				m_registers.program_counter() += 2;
			m_registers.program_counter() += 2;
			break;
		case 0xA000: // I = NNN
			m_registers.index() = nnn;
			m_registers.program_counter() += 2;
			break;
		case 0xB000: // PC = V0 + NNN
			m_registers.program_counter() = m_registers.v(0) + nnn;
			break;
		case 0xC000: // Vx = rand() & NN
			m_registers.v(x) = std::uniform_int_distribution<uint8_t>(0, 255)(m_random_engine) & nn;
			m_registers.program_counter() += 2;
			break;
		case 0xD000: // draw(Vx,Vy,N)
			m_registers.v(0xF) = 0;
			for (uint8_t yo = 0; yo < n; yo++) {
				uint8_t pixel = m_memory.at(m_registers.index() + yo);
				uint8_t row = (m_registers.v(y) + yo);
				if (row >= Screen::HEIGHT)
					continue;
				for (uint8_t xo = 0; xo < 8; xo++) {
					if ((pixel & (0x80 >> xo)) == 0)
						continue;
					uint8_t col = (m_registers.v(x) + xo);
					if (col >= Screen::WIDTH)
						continue;
					if (m_screen.at(col, row))
						m_registers.v(0xF) = 1;
					m_screen.at(col, row) ^= true;
				}
			}
			m_registers.program_counter() += 2;
			break;
		case 0xE000:
			switch (opcode & 0x00FF) {
				case 0x009E: // skip next if key[Vx]
					if (m_keyboard.key(m_registers.v(x)))
						m_registers.program_counter() += 2;
					m_registers.program_counter() += 2;
					break;
				case 0x00A1: // skip next if !key[Vx]
					if (!m_keyboard.key(m_registers.v(x)))
						m_registers.program_counter() += 2;
					m_registers.program_counter() += 2;
					break;
				default:
					invalid = true;
					break;
			}
			break;
		case 0xF000:
			switch (opcode & 0x00FF) {
				case 0x0007: // Vx = delay_timer
					m_registers.v(x) = m_delay_timer.time();
					m_registers.program_counter() += 2;
					break;
				case 0x000A: // wait Vx = key
					if (m_keyboard.last_key() == Keyboard::KEY_NONE)
						m_keyboard.last_key() = Keyboard::KEY_WAIT;
					if (m_keyboard.last_key() != Keyboard::KEY_WAIT) {
						m_registers.v(x) = m_keyboard.last_key();
						m_keyboard.last_key() = Keyboard::KEY_NONE;
						m_registers.program_counter() += 2;
					}
					break;
				case 0x0015: // delay_timer = Vx
					m_delay_timer.time() = m_registers.v(x);
					m_registers.program_counter() += 2;
					break;
				case 0x0018: // sound_timer = Vx
					m_sound_timer.time() = m_registers.v(x);
					m_registers.program_counter() += 2;
					break;
				case 0x001E: // I += Vx (with carry)
					m_registers.v(0xF) = m_registers.index() + m_registers.v(x) > 0x0FFF ? 1 : 0;
					m_registers.index() += m_registers.v(x);
					m_registers.program_counter() += 2;
					break;
				case 0x0029: // I = Vx * 5
					m_registers.index() = m_registers.v(x) * 5;
					m_registers.program_counter() += 2;
					break;
				case 0x0033: // store Vx as BCD at I[0..2]
					m_memory.at(m_registers.index())     = (m_registers.v(x) / 100) % 10;
					m_memory.at(m_registers.index() + 1) = (m_registers.v(x) / 10)  % 10;
					m_memory.at(m_registers.index() + 2) = (m_registers.v(x))       % 10;
					m_registers.program_counter() += 2;
					break;
				case 0x0055: // store V0..Vx at I[0..x]
					for (uint8_t i = 0; i <= x; i++) {
						m_memory.at(m_registers.index() + i) = m_registers.v(i);
					}
					m_registers.index() += static_cast<uint16_t>(x + 1);
					m_registers.program_counter() += 2;
					break;
				case 0x0065: // load V0..Vx from I[0..x]
					for (uint8_t i = 0; i <= x; i++) {
						m_registers.v(i) = m_memory.at(m_registers.index() + i);
					}
					m_registers.index() += static_cast<uint16_t>(x + 1);
					m_registers.program_counter() += 2;
					break;
				default:
					invalid = true;
					break;
			}
			break;
		break;
	}

	if (invalid) {
		std::cerr << "Error: invalid opcode 0x" <<std::setw(4) << std::setfill('0') <<  std::hex << opcode << std::endl;
		exit(EXIT_FAILURE);
	}
}

} // namespace trabalho