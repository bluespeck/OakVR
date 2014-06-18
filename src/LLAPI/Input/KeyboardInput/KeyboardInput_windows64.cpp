#include "KeyboardInput.h"
#include <Windows.h>
#include <unordered_map>

#include "Profiler/Profiler.h"

namespace oakvr
{
	namespace input
	{

		class KeyboardInput::KeyboardInputImpl
		{
		public:

			KeyboardInputImpl();

			uint8_t keyStatesCurrent[256];
			uint8_t keyStatesPrevious[256];

			std::unordered_map<Key, int> keyMap;
		};

		void KeyboardInput::Update()
		{
			PROFILER_FUNC_SCOPED_TIMER;
			memcpy(m_pImpl->keyStatesPrevious, m_pImpl->keyStatesCurrent, 256 * sizeof(m_pImpl->keyStatesPrevious[0]));
			//memset(m_pImpl->keyStatesCurrent, 0, 256 * sizeof(m_pImpl->keyStatesPrevious[0]));
			GetKeyboardState(m_pImpl->keyStatesCurrent);
		}

		bool KeyboardInput::IsPressed(Key key) const
		{
			PROFILER_FUNC_SCOPED_TIMER;
			int keyCode = m_pImpl->keyMap.at(key);
			return ((m_pImpl->keyStatesCurrent[keyCode] & 0x80) != 0) && !((m_pImpl->keyStatesPrevious[keyCode] & 0x80) != 0);
		}

		bool KeyboardInput::IsHeld(Key key) const
		{
			PROFILER_FUNC_SCOPED_TIMER;
			int keyCode = m_pImpl->keyMap.at(key);
			return ((m_pImpl->keyStatesCurrent[keyCode] & 0x80) != 0) && ((m_pImpl->keyStatesPrevious[keyCode] & 0x80) != 0);
		}

		bool KeyboardInput::IsReleased(Key key) const
		{
			PROFILER_FUNC_SCOPED_TIMER;
			int keyCode = m_pImpl->keyMap.at(key);
			return !((m_pImpl->keyStatesCurrent[keyCode] & 0x80) != 0) && ((m_pImpl->keyStatesPrevious[keyCode] & 0x80) != 0);
		}

		bool KeyboardInput::IsDown(Key key) const
		{
			PROFILER_FUNC_SCOPED_TIMER;
			int keyCode = m_pImpl->keyMap.at(key);
			return ((m_pImpl->keyStatesCurrent[keyCode] & 0x80) != 0);
		}

		bool KeyboardInput::IsUp(Key key) const
		{
			PROFILER_FUNC_SCOPED_TIMER;
			int keyCode = m_pImpl->keyMap.at(key);
			return !((m_pImpl->keyStatesCurrent[keyCode] & 0x80) != 0);
		}

		KeyboardInput::KeyboardInputImpl::KeyboardInputImpl()
		{
			keyMap = std::unordered_map<Key, int>{ 
					{ Key::a, 0x41 },
					{ Key::b, 0x42 },
					{ Key::c, 0x43 },
					{ Key::d, 0x44 },
					{ Key::e, 0x45 },
					{ Key::f, 0x46 },
					{ Key::g, 0x47 },
					{ Key::h, 0x48 },
					{ Key::i, 0x49 },
					{ Key::j, 0x4A },
					{ Key::k, 0x4B },
					{ Key::l, 0x4C },
					{ Key::m, 0x4D },
					{ Key::n, 0x4E },
					{ Key::o, 0x4F },
					{ Key::p, 0x50 },
					{ Key::q, 0x51 },
					{ Key::r, 0x52 },
					{ Key::s, 0x53 },
					{ Key::t, 0x54 },
					{ Key::u, 0x55 },
					{ Key::v, 0x56 },
					{ Key::w, 0x57 },
					{ Key::x, 0x58 },
					{ Key::y, 0x59 },
					{ Key::z, 0x5A },

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

					{ Key::enter, VK_RETURN },
					{ Key::space, VK_SPACE },
					{ Key::backspace, VK_BACK },
					{ Key::insert, VK_INSERT },
					{ Key::del, VK_DELETE },

					{ Key::lControl, VK_LCONTROL},
					{ Key::rControl, VK_RCONTROL },
					{ Key::lAlt, VK_LMENU },
					{ Key::rAlt, VK_RMENU },
					{ Key::lWin, VK_LWIN },
					{ Key::rWin, VK_RWIN },
					{ Key::lShift, VK_LSHIFT },
					{ Key::rShift, VK_RSHIFT },

					{ Key::left, VK_LEFT },
					{ Key::up, VK_UP },
					{ Key::right, VK_RIGHT },
					{ Key::down, VK_DOWN },

					{ Key::home, VK_HOME },

					{ Key::f1, VK_F1 },
					{ Key::f2, VK_F2 },
					{ Key::f3, VK_F3 },
					{ Key::f4, VK_F4 },
					{ Key::f5, VK_F5 },
					{ Key::f6, VK_F6 },
					{ Key::f7, VK_F7 },
					{ Key::f8, VK_F8 },
					{ Key::f9, VK_F9 },
					{ Key::f10, VK_F10 },
					{ Key::f11, VK_F11 },
					{ Key::f12, VK_F12 },

					{ Key::pageUp, VK_PRIOR },
					{ Key::pageDown, VK_NEXT },
					
					{ Key::esc, VK_ESCAPE },
					{ Key::tab, VK_TAB },
					{ Key::capsLock, VK_CAPITAL },
					
					{ Key::num0, VK_NUMPAD0 },
					{ Key::num1, VK_NUMPAD1 },
					{ Key::num2, VK_NUMPAD2 },
					{ Key::num3, VK_NUMPAD3 },
					{ Key::num4, VK_NUMPAD4 },
					{ Key::num5, VK_NUMPAD5 },
					{ Key::num6, VK_NUMPAD6 },
					{ Key::num7, VK_NUMPAD7 },
					{ Key::num8, VK_NUMPAD8 },
					{ Key::num9, VK_NUMPAD9 },

					{ Key::divide, VK_DIVIDE },
					{ Key::subtract, VK_SUBTRACT },
					{ Key::add, VK_ADD },
					{ Key::numLock, VK_NUMLOCK },
					{ Key::numEnter, VK_RETURN },	// no way to differentiate from the other 'enter' key with this approach

					{ Key::backtick_tilde, VK_OEM_3 },
					{ Key::minus_underscore, VK_OEM_MINUS },
					{ Key::equal_plus, VK_OEM_PLUS },
					{ Key::lBracket_curly, VK_OEM_4 },
					{ Key::rBracket_curly, VK_OEM_6 },
					{ Key::backslash_pipe, VK_OEM_5 },
					{ Key::semicolon_colon, VK_OEM_1 },
					{ Key::singleQuote_doubleQuote, VK_OEM_7 },
					{ Key::comma_less, VK_OEM_COMMA },
					{ Key::period_greater, VK_OEM_PERIOD },
					{ Key::slash_questionMark, VK_OEM_2 },

					{ Key::printScreen, VK_PRINT }
			}; // keymap initializer list end
		}

		KeyboardInput::KeyboardInput()
			: m_pImpl{ std::make_unique<KeyboardInputImpl>() }
		{

		}

		KeyboardInput::~KeyboardInput()
		{

		}
	} // namespace input
} // namespace oakvr