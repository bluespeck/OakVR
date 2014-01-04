#pragma once

#include <string>
#include <memory>

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
			void Minimize();
			void Maximize();
			void RestoreSize();
			void SwapBuffers();

			void SetPositionX( int posX );
			int GetPositionX();

			void SetPositionY( int posY );
			int GetPositionY();

			void SetWidth( unsigned int width );
			inline unsigned int GetWidth();
			
			void SetHeight( unsigned int height );
			inline unsigned int GetHeight();

			const std::string &GetTitle();
			void SetTitle(const std::string &title);

			long int GetOSHandle() { return m_osHandle; }

						
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
			bool m_bFullScreen;
			WindowState m_windowState;
			
			long int m_osHandle;
			class RenderWindowImpl;
#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
			friend LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif
			std::unique_ptr<RenderWindowImpl> m_pImpl;
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
