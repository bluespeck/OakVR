
#include "../Oak3DCoreConfig.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS


#include "WindowsRenderWindow.h"

#include <windows.h>

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		WindowsRenderWindow::WindowsRenderWindow()
		: Oak3D::Core::RenderWindow()
		{
		}

		// --------------------------------------------------------------------------------
		WindowsRenderWindow::WindowsRenderWindow(const std::wstring &name, int posX, int posY, unsigned int width, unsigned int height)
		: RenderWindow( name, posX, posY, width, height)
		{
		}

		// --------------------------------------------------------------------------------
		LRESULT WindowsRenderWindow::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			if (uMsg == WM_NCCREATE)
			{
				// Get window object pointer from create params
				SetWindowLong(hWnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
			}
						
			WindowsRenderWindow* pWnd = (WindowsRenderWindow *)GetWindowLong(hWnd, GWL_USERDATA);

			if(pWnd)
				return pWnd->WindowsMessageHandler(hWnd, uMsg, wParam, lParam);
			else
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		// --------------------------------------------------------------------------------
		void WindowsRenderWindow::Initialize()
		{
			HINSTANCE hInstance = GetModuleHandle(nullptr);

			WNDCLASSEX wcex;

			// clear out the window class for use
			ZeroMemory(&wcex, sizeof(WNDCLASSEX));

			wcex.cbSize = sizeof(WNDCLASSEX); 
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = (WNDPROC)WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = 0;
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			
			wcex.lpszMenuName = 0;
			wcex.lpszClassName = L"WindowsRenderWindowClass";
			wcex.hIconSm = 0;

			RegisterClassEx(&wcex);

			RECT wr = {0, 0, m_width, m_height};    // set the size, but not the position
			AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

			// Pass a pointer to this object as the lParam in order to later use it to process window messages using the object's methods
			HWND hWnd = CreateWindowEx(0, L"WindowsRenderWindowClass", m_title.c_str(), WS_OVERLAPPEDWINDOW, m_posX, m_posY, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInstance, this);
			m_osHandle = reinterpret_cast<long int>(hWnd);
			
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
		}

		// --------------------------------------------------------------------------------
		void WindowsRenderWindow::Minimize()
		{

		}

		// --------------------------------------------------------------------------------
		void WindowsRenderWindow::Maximize()
		{
		}

		// --------------------------------------------------------------------------------
		void WindowsRenderWindow::RestoreSize()
		{

		}

		// --------------------------------------------------------------------------------
		LRESULT WindowsRenderWindow::WindowsMessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch(uMsg)
			{
			case WM_DESTROY:
				{
					// close the application entirely
					PostQuitMessage(0);
					return 0;
				} 
				break;
			default:
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
				break;
			}
			return 0;
		}

	} // namespace Core
} // namespace Oak3D

#endif // OAK3D_OS == OAK3D_OS_WINDOWS
