#pragma once

#include <string>
#include <memory>

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
			RenderWindow(RenderWindow &&rw) = default;
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
			unsigned int GetWidth();
			
			void SetHeight( unsigned int height );
			unsigned int GetHeight();

			const std::string &GetTitle();
			void SetTitle(const std::string &title);
						
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
			std::unique_ptr<RenderWindowImpl> m_pImpl;
		};

	} // namespace Render
} // namespace oakvr
