#include <memory>

#include "Common.h"
#include "Renderer/Renderer/RenderWindow.h"
#include "Log/Log.h"

namespace oakvr
{
	namespace render
	{
		class RenderWindow::RenderWindowImpl
		{
		public:
			HWND hWnd;
			std::unique_ptr<RenderWindow> m_pParent;
		public:
			LRESULT WindowsMessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			friend LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		};

		LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow()
		: m_pImpl { new RenderWindowImpl() }
		, m_windowState { eWS_Normal}
		, m_bFullScreen { false }
		, m_posX { 0 }
		, m_posY { 0 }
		, m_width { 1024 }
		, m_height { 768 }
		, m_title { "oakvr [OpenGL]" }
		{
			
		}

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow(const std::string &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title{ title }, m_posX{ posX }, m_posY{ posY }, m_width{ width }, m_height{ height }, m_pImpl{ new RenderWindowImpl() }
		{

		}

		// --------------------------------------------------------------------------------
		RenderWindow::~RenderWindow()
		{
		}
		
		// --------------------------------------------------------------------------------
		bool RenderWindow::Initialize()
		{
			HINSTANCE hInstance = GetModuleHandle(nullptr);

			WNDCLASSEXW wcex;

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

			RegisterClassExW(&wcex);

			RECT wr = { 0, 0, m_width, m_height };    // set the size, but not the position
			AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

			// Pass a pointer to this object as the lParam in order to later use it to process window messages using the object's methods
			HWND hWnd = CreateWindowExW(0, L"WindowsRenderWindowClass", L"oakvr [OpenGL]", WS_OVERLAPPEDWINDOW, m_posX, m_posY, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInstance, &m_pImpl);
			m_pImpl->hWnd = hWnd;
			m_osHandle = reinterpret_cast<long int>(hWnd);
			SetWindowTextA(hWnd, m_title.c_str());
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);

			Log::PrintInfo("RW Initialized!\n");

			return true;
		}
		
		bool RenderWindow::IsOpen()
		{
			return true;
		}

		void RenderWindow::SwapBuffers()
		{
			if (IsOpen())
				::SwapBuffers(GetDC((HWND)m_osHandle));
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Minimize()
		{

		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Maximize()
		{
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::RestoreSize()
		{

		}


		// --------------------------------------------------------------------------------
		LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			if (uMsg == WM_CREATE)
			{
				std::unique_ptr<RenderWindow::RenderWindowImpl> &uptr = *(std::unique_ptr<RenderWindow::RenderWindowImpl>*)lParam;
				return uptr->WindowsMessageHandler(hWnd, uMsg, wParam, lParam);
			}
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}

		// --------------------------------------------------------------------------------
		LRESULT RenderWindow::RenderWindowImpl::WindowsMessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_CREATE:
				//InitializeOpenGL(hWnd);
				break;
			case WM_DESTROY:
				// close the application entirely
				PostQuitMessage(0);
				return 0;
			case WM_SIZE:
				m_pParent->m_width = LOWORD(lParam);
				m_pParent->m_height = HIWORD(lParam);
				break;
			case WM_MOVE:
				m_pParent->m_posX = LOWORD(lParam);
				m_pParent->m_posY = HIWORD(lParam);
				break;
			default:
				return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				break;
			}
			return 0;
		}

	} // namespace render
} // namespace oakvr