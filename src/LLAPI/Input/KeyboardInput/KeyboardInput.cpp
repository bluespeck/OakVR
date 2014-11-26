#pragma once

#include "KeyboardInput.h"

#include <unordered_map>

namespace oakvr
{
	namespace input
	{
		auto KeyboardInput::ToASCII(Key key) const -> char
		{
			static auto keyToAsciiMap = std::unordered_map<Key, int>{ 
					{ Key::a, 0x61 },
					{ Key::b, 0x62 },
					{ Key::c, 0x63 },
					{ Key::d, 0x64 },
					{ Key::e, 0x65 },
					{ Key::f, 0x66 },
					{ Key::g, 0x67 },
					{ Key::h, 0x68 },
					{ Key::i, 0x69 },
					{ Key::j, 0x6A },
					{ Key::k, 0x6B },
					{ Key::l, 0x6C },
					{ Key::m, 0x6D },
					{ Key::n, 0x6E },
					{ Key::o, 0x6F },
					{ Key::p, 0x70 },
					{ Key::q, 0x71 },
					{ Key::r, 0x72 },
					{ Key::s, 0x73 },
					{ Key::t, 0x74 },
					{ Key::u, 0x75 },
					{ Key::v, 0x76 },
					{ Key::w, 0x77 },
					{ Key::x, 0x78 },
					{ Key::y, 0x79 },
					{ Key::z, 0x7A },

					{ Key::_0, 0x30 },
					{ Key::_1, 0x31 },
					{ Key::_2, 0x32 },
					{ Key::_3, 0x33 },
					{ Key::_4, 0x34 },
					{ Key::_5, 0x35 },
					{ Key::_6, 0x36 },
					{ Key::_7, 0x37 },
					{ Key::_8, 0x38 },
					{ Key::_9, 0x39 },

					{ Key::enter, -1 },
					{ Key::space, 32 },
					{ Key::backspace, -1 },
					{ Key::insert, -1 },
					{ Key::del, -1 },

					{ Key::lControl, -1},
					{ Key::rControl, -1 },
					{ Key::lAlt, -1 },
					{ Key::rAlt, -1 },
					{ Key::lWin, -1 },
					{ Key::rWin, -1 },
					{ Key::lShift, -1 },
					{ Key::rShift, -1 },

					{ Key::left, 	-1 },
					{ Key::up, 		-1 },
					{ Key::right, 	-1 },
					{ Key::down, 	-1 },

					{ Key::home, 	-1 },
					{ Key::end, 	-1 },

					{ Key::f1, -1 },
					{ Key::f2, -1 },
					{ Key::f3, -1 },
					{ Key::f4, -1 },
					{ Key::f5, -1 },
					{ Key::f6, -1 },
					{ Key::f7, -1 },
					{ Key::f8, -1 },
					{ Key::f9, -1 },
					{ Key::f10, -1 },
					{ Key::f11, -1 },
					{ Key::f12, -1 },

					{ Key::pageUp, -1 },
					{ Key::pageDown, -1 },
					
					{ Key::esc, -1 },
					{ Key::tab, -1 },
					{ Key::capsLock, -1 },
					
					{ Key::num0, 48+0 },
					{ Key::num1, 48+1 },
					{ Key::num2, 48+2 },
					{ Key::num3, 48+3 },
					{ Key::num4, 48+4 },
					{ Key::num5, 48+5 },
					{ Key::num6, 48+6 },
					{ Key::num7, 48+7 },
					{ Key::num8, 48+8 },
					{ Key::num9, 48+9 },

					{ Key::divide, '/' },
					{ Key::multiply, '*' },
					{ Key::subtract, '-' },
					{ Key::add, '+' },
					{ Key::numLock, -1 },
					{ Key::numEnter, -1 },
					{ Key::decimal, '.' },

					{ Key::backtick_tilde, '`' },
					{ Key::minus_underscore, '-' },
					{ Key::equal_plus, '=' },
					{ Key::lBracket_curly, '[' },
					{ Key::rBracket_curly, ']' },
					{ Key::backslash_pipe, '\\' },
					{ Key::semicolon_colon, ';' },
					{ Key::singleQuote_doubleQuote, '\'' },
					{ Key::comma_less, ',' },
					{ Key::period_greater, '.' },
					{ Key::slash_questionMark, '/' },

					{ Key::printScreen, -1 }
			}; // keymap initializer list end

			return keyToAsciiMap.at(key);
		}

		void KeyboardInput::Capture(void *pCaptor)
		{
			m_pCaptor = pCaptor;
		}

		void KeyboardInput::Release()
		{
			m_pCaptor = nullptr;
		}

		auto KeyboardInput::GetCaptor() const -> void*
		{
			return m_pCaptor;
		}
	}
}
