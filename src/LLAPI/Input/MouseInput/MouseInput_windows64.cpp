#include <Windows.h>

#include "MouseInput.h"

namespace oakvr
{
	namespace input
	{
		LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

		class MouseInput::MouseInputImpl
		{
		public:
			MouseInputImpl();

			static void HandleMessage(WPARAM wParam, LPARAM lParam);
			static MouseInputImpl *m_pInstance;
			struct MouseState
			{
				int32_t m_wheelDelta;
				int32_t m_x, m_y;
				bool m_bLButtonDown;
				bool m_bMButtonDown;
				bool m_bRButtonDown;
			} m_previousState, m_currentState;

			volatile MouseState m_volatileState;

		};

		MouseInput::MouseInputImpl* MouseInput::MouseInputImpl::m_pInstance = nullptr;

		// --------------------------------------------------------------------------------
		MouseInput::MouseInput()
		{
			m_pImpl = new MouseInputImpl();
			//::SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);
		}

		// --------------------------------------------------------------------------------
		MouseInput::~MouseInput()
		{
			delete m_pImpl;
		}

		// --------------------------------------------------------------------------------
		void MouseInput::Update()
		{
			memcpy(&m_pImpl->m_previousState, &m_pImpl->m_currentState, sizeof(MouseInputImpl::MouseState));

			// retrieve current cursor position
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			m_pImpl->m_currentState.m_x = cursorPos.x;
			m_pImpl->m_currentState.m_y = cursorPos.y;

			m_pImpl->m_currentState.m_bLButtonDown = (GetKeyState(VK_LBUTTON) & 0x100) != 0;
			m_pImpl->m_currentState.m_bMButtonDown = (GetKeyState(VK_MBUTTON) & 0x100) != 0;
			m_pImpl->m_currentState.m_bRButtonDown = (GetKeyState(VK_RBUTTON) & 0x100) != 0;
			
			//memcpy(&m_pImpl->m_currentState, (const void *)&m_pImpl->m_volatileState, sizeof(MouseInputImpl::MouseState));
			//m_pImpl->m_volatileState.m_wheelDelta = 0;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonDown() const
		{
			return m_pImpl->m_currentState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonDown() const
		{
			return m_pImpl->m_currentState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonDown() const
		{
			return m_pImpl->m_currentState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonUp() const
		{
			return !m_pImpl->m_currentState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonUp() const
		{
			return !m_pImpl->m_currentState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonUp() const
		{
			return !m_pImpl->m_currentState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonHeld() const
		{
			return m_pImpl->m_currentState.m_bLButtonDown && m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonHeld() const
		{
			return m_pImpl->m_currentState.m_bMButtonDown && m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonHeld() const
		{
			return m_pImpl->m_currentState.m_bRButtonDown && m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonPressed() const
		{
			return m_pImpl->m_currentState.m_bLButtonDown && !m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonPressed() const
		{
			return m_pImpl->m_currentState.m_bMButtonDown && !m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonPressed() const
		{
			return m_pImpl->m_currentState.m_bRButtonDown && !m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonReleased() const
		{
			return !m_pImpl->m_currentState.m_bLButtonDown && m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonReleased() const
		{
			return !m_pImpl->m_currentState.m_bMButtonDown && m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonReleased() const
		{
			return !m_pImpl->m_currentState.m_bRButtonDown && m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::HasMouseMoved() const
		{
			return (m_pImpl->m_previousState.m_x != m_pImpl->m_currentState.m_x) || (m_pImpl->m_previousState.m_y != m_pImpl->m_currentState.m_y);
		}

		// --------------------------------------------------------------------------------
		std::pair<float, float> MouseInput::GetPosition() const
		{
			return std::make_pair(m_pImpl->m_currentState.m_x, m_pImpl->m_currentState.m_y);
		}

		// --------------------------------------------------------------------------------
		std::pair<float, float> MouseInput::GetPositionDelta() const
		{
			return std::make_pair(m_pImpl->m_currentState.m_x - m_pImpl->m_previousState.m_x, m_pImpl->m_currentState.m_y - m_pImpl->m_previousState.m_y);
		}

		// --------------------------------------------------------------------------------
		int32_t MouseInput::GetWheelDelta() const
		{
			return m_pImpl->m_currentState.m_wheelDelta;
		}

		// --------------------------------------------------------------------------------
		MouseInput::MouseInputImpl::MouseInputImpl()
		{
			m_pInstance = this;	// to be used by HandleMessage
			m_volatileState.m_bLButtonDown = false;
			m_volatileState.m_bMButtonDown = false;
			m_volatileState.m_bRButtonDown = false;
			m_volatileState.m_x = 0;
			m_volatileState.m_y = 0;
			m_volatileState.m_wheelDelta = 0;

		}

		// --------------------------------------------------------------------------------
		void MouseInput::MouseInputImpl::HandleMessage(WPARAM wParam, LPARAM lParam)
		{

			MSLLHOOKSTRUCT msllhs = *(MSLLHOOKSTRUCT *)lParam;

			switch (wParam)
			{
			case WM_MOUSEMOVE:
				//::ScreenToClient((HWND)oakvr::Engine::GetRenderWindow()->GetOSHandle(), &msllhs.pt);
				m_pInstance->m_volatileState.m_x = msllhs.pt.x;
				m_pInstance->m_volatileState.m_y = msllhs.pt.y;
				break;
			case WM_LBUTTONDOWN:
				m_pInstance->m_volatileState.m_bLButtonDown = true;
				break;
			case WM_MBUTTONDOWN:
				m_pInstance->m_volatileState.m_bMButtonDown = true;
				break;
			case WM_RBUTTONDOWN:
				m_pInstance->m_volatileState.m_bRButtonDown = true;
				break;
			case WM_MOUSEWHEEL:
				m_pInstance->m_volatileState.m_wheelDelta = (int16_t)HIWORD(msllhs.mouseData);
				break;
			case WM_LBUTTONUP:
				m_pInstance->m_volatileState.m_bLButtonDown = false;
				break;
			case WM_MBUTTONUP:
				m_pInstance->m_volatileState.m_bMButtonDown = false;
				break;
			case WM_RBUTTONUP:
				m_pInstance->m_volatileState.m_bRButtonDown = false;
				break;
			default:
				break;
			}
		}

		// --------------------------------------------------------------------------------
		void *MouseInput::GetMouseOwner()
		{
			return m_pMouseOwner;
		}

		// --------------------------------------------------------------------------------
		void *MouseInput::SetMouseOwner(void *newOwner)
		{
			void * oldOwner = m_pMouseOwner;
			m_pMouseOwner = newOwner;
			return oldOwner;
		}

		// --------------------------------------------------------------------------------
		LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode == 0)
			{
				MouseInput::MouseInputImpl::HandleMessage(wParam, lParam);
			}

			return CallNextHookEx(0, nCode, wParam, lParam);
		}
	}
}
