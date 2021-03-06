#pragma once

#include "Utils/Singleton.h"
#include "Utils/Types.h"

#include <cstdint>
#include <vector>

namespace oakvr
{
	namespace input
	{
		enum class Key : uint8_t
		{
			__first,
			_0 = __first, _1, _2, _3, _4, _5, _6, _7, _8, _9,
			
			a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
			
			enter,
			space,
			backspace,
			insert,
			del,

			lControl,
			rControl,
			lAlt,
			rAlt,
			lWin,
			rWin,
			lShift,
			rShift,

			left, 
			up,
			right,
			down,
			
			home,
			end,			
			
			f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,

			pageUp,
			pageDown,

			esc,
			tab,
			capsLock,

			num0, num1, num2, num3, num4, num5, num6, num7, num8, num9,
			divide, multiply, subtract, add,
			numLock, numEnter, decimal,

			backtick_tilde, minus_underscore, equal_plus,
			lBracket_curly, rBracket_curly, backslash_pipe,
			semicolon_colon, singleQuote_doubleQuote,
			comma_less, period_greater, slash_questionMark,

			printScreen,
			__last = printScreen
		};

		class KeyboardInput : public oakvr::Singleton<KeyboardInput>
		{
		public:
			class KeyboardInputImpl;

			KeyboardInput();
			~KeyboardInput();
			
			void Update();

			bool IsPressed(Key key) const;
			bool IsHeld(Key key) const;
			bool IsReleased(Key key) const;
			bool IsDown(Key key) const;
			bool IsUp(Key key) const;
			auto GetKeysPressed() const->std::vector < Key > ;
			auto ToASCII(Key key) const -> char;

			void Capture(void *);
			void Release();
			auto GetCaptor() const -> void*;
			
		private:
			up<KeyboardInputImpl> m_pImpl;
			void *m_pCaptor = nullptr;
			
		};

		namespace keyboard
		{
			inline auto Update() -> void			{ KeyboardInput::GetInstance().Update(); }
			inline auto IsPressed(Key key) -> bool	{ return KeyboardInput::GetInstance().IsPressed(key); }
			inline auto IsHeld(Key key) -> bool		{ return KeyboardInput::GetInstance().IsHeld(key); }
			inline auto IsReleased(Key key) -> bool { return KeyboardInput::GetInstance().IsReleased(key); }
			inline auto IsDown(Key key) -> bool		{ return KeyboardInput::GetInstance().IsDown(key); }
			inline auto IsUp(Key key) -> bool		{ return KeyboardInput::GetInstance().IsUp(key); }
			inline auto GetKeysPressed() -> std::vector < Key > { return KeyboardInput::GetInstance().GetKeysPressed(); }
			inline auto ToASCII(Key key) -> char	{ return KeyboardInput::GetInstance().ToASCII(key); }
			inline auto Capture(void *p) -> void	{ KeyboardInput::GetInstance().Capture(p); }
			inline auto Release() -> void			{ KeyboardInput::GetInstance().Release(); }
			inline auto GetCaptor() -> void*		{ return KeyboardInput::GetInstance().GetCaptor(); }
		}
	}
}
