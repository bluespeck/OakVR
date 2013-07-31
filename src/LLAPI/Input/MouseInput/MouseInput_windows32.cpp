#include <windows.h>

#include "MouseInput.h"

namespace oakvr
{
	namespace Input
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
				bool m_bLButtonDown;
				bool m_bMButtonDown;
				bool m_bRButtonDown;
				int32_t m_wheelDelta;
				uint32_t m_x, m_y;
			} m_previousState, m_currentState;

			volatile MouseState m_volatileState;
			
		};

		MouseInput::MouseInputImpl* MouseInput::MouseInputImpl::m_pInstance = nullptr;

		// --------------------------------------------------------------------------------
		MouseInput::MouseInput()
		{
			m_pImpl = new MouseInputImpl();
			::SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);
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
			memcpy(&m_pImpl->m_currentState, (const void *)&m_pImpl->m_volatileState, sizeof(MouseInputImpl::MouseState));
			m_pImpl->m_volatileState.m_wheelDelta = 0;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonDown()
		{
			return m_pImpl->m_currentState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonDown()
		{
			return m_pImpl->m_currentState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonDown()
		{
			return m_pImpl->m_currentState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonUp()
		{
			return !m_pImpl->m_currentState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonUp()
		{
			return !m_pImpl->m_currentState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonUp()
		{
			return !m_pImpl->m_currentState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonHeld()
		{
			return m_pImpl->m_currentState.m_bLButtonDown && m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonHeld()
		{
			return m_pImpl->m_currentState.m_bMButtonDown && m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonHeld()
		{
			return m_pImpl->m_currentState.m_bRButtonDown && m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonPressed()
		{
			return m_pImpl->m_currentState.m_bLButtonDown && !m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonPressed()
		{
			return m_pImpl->m_currentState.m_bMButtonDown && !m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonPressed()
		{
			return m_pImpl->m_currentState.m_bRButtonDown && !m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsLeftButtonReleased()
		{
			return !m_pImpl->m_currentState.m_bLButtonDown && m_pImpl->m_previousState.m_bLButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsMiddleButtonReleased()
		{
			return !m_pImpl->m_currentState.m_bMButtonDown && m_pImpl->m_previousState.m_bMButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::IsRightButtonReleased()
		{
			return !m_pImpl->m_currentState.m_bRButtonDown && m_pImpl->m_previousState.m_bRButtonDown;
		}

		// --------------------------------------------------------------------------------
		bool MouseInput::HasMouseMoved()
		{
			return (m_pImpl->m_previousState.m_x != m_pImpl->m_currentState.m_x) || (m_pImpl->m_previousState.m_y != m_pImpl->m_currentState.m_y);
		}

		// --------------------------------------------------------------------------------
		std::pair<int32_t, int32_t> MouseInput::GetPosition()
		{			
			return std::make_pair(m_pImpl->m_currentState.m_x, m_pImpl->m_currentState.m_y);
		}

		// --------------------------------------------------------------------------------
		std::pair<int32_t, int32_t> MouseInput::GetPositionDelta()
		{
			return std::make_pair(m_pImpl->m_currentState.m_x - m_pImpl->m_previousState.m_x, m_pImpl->m_currentState.m_y - m_pImpl->m_previousState.m_y);
		}

		// --------------------------------------------------------------------------------
		int32_t MouseInput::GetWheelDelta()
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
			
			switch(wParam)
			{
			case WM_MOUSEMOVE:
				//::ScreenToClient((HWND)ro3d::Engine::GetRenderWindow()->GetOSHandle(), &msllhs.pt);
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
			if(nCode == 0)
			{
				MouseInput::MouseInputImpl::HandleMessage(wParam, lParam);
			}

			return CallNextHookEx(0, nCode, wParam, lParam);
		}
	}
}
