#pragma once

#include <string>
#include <memory>
#include <functional>

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
#	include <Windows.h>
#endif

namespace oakvr
{
	namespace render
	{
		class RenderWindow
		{
		public:
			RenderWindow();
			RenderWindow( const std::string &title, int posX, int posY, unsigned int width, unsigned int height);
			RenderWindow(const RenderWindow &rw) = delete;
			//RenderWindow(RenderWindow &&rw) = default;
			RenderWindow& operator=(const RenderWindow &rw) = delete;
			~RenderWindow();
			
			bool Initialize();
			bool IsOpen();
			bool IsValid(); // true if it is backed by a valid render context
			void Minimize();
			void Maximize();
			void RestoreSize();
			void SwapBuffers();

			
			inline int GetPositionX() const { return m_posX; }
			inline int GetPositionY() const { return m_posY; }
			void SetPosition(int x, int y);

			inline unsigned int GetWidth();
			inline unsigned int GetHeight();
			void SetSize(unsigned int width, unsigned int height);

			void SetWindowSizeCallback(void(*f)(void *, int, int));
			void SetWindowFocusCallback(void(*f)(void *, int));
			void SetWindowPositionCallback(void(*f)(void *, int, int));

			const std::string &GetTitle() { return m_title; }
			void SetTitle(const std::string &title);

			long int GetNativeHandle() { return m_nativeHandle; }

			inline bool HasFocus() const { return m_bHasFocus; }
			void OnFocusChanged(bool focused) { m_bHasFocus = focused; }

			void OnPositionChanged(int x, int y) { m_posX = x; m_posY = y; }

		private:

			enum WindowState
			{
				eWS_Normal,
				eWS_Minimized,
				eWS_Maximized
			};

			std::string m_title;
			int m_posX, m_posY;
			unsigned int m_width, m_height;
			WindowState m_windowState;
			
			long int m_nativeHandle;

			class RenderWindowImpl;
			std::unique_ptr<RenderWindowImpl> m_pImpl;

			bool m_bFullScreen = false;
			bool m_bHasFocus = false;

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
			friend LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

		};

		inline unsigned int RenderWindow::GetWidth()
		{
			return m_width;
		}

		inline unsigned int RenderWindow::GetHeight()
		{
			return m_height;
		}

	} // namespace render
} // namespace oakvr
