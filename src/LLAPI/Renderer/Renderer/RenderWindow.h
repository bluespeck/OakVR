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
			
			void Initialize();
			void Minimize();
			void Maximize();
			void RestoreSize();
			void Refresh();

			void SetOSHandle( long int handle );
			long int GetOSHandle();
			
			void SetPositionX( int posX );
			int GetPositionX();

			void SetPositionY( int posY );
			int GetPositionY();

			void SetWidth( unsigned int width );
			unsigned int GetWidth();
			
			inline void SetHeight( unsigned int height );
			inline unsigned int GetHeight();

			virtual const std::string &GetTitle(){ return m_title; }
			virtual void SetTitle(const std::string &title) { m_title = title; }
						
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

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetOSHandle(long int handle)
		{
			m_osHandle = handle;
		}

		// --------------------------------------------------------------------------------
		inline long int RenderWindow::GetOSHandle()
		{
			return m_osHandle;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetPositionX(int posX)
		{
			m_posX = posX;
		}

		// --------------------------------------------------------------------------------
		inline int RenderWindow::GetPositionX()
		{
			return m_posX;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetPositionY(int posY)
		{
			m_posY = posY;
		}

		// --------------------------------------------------------------------------------
		inline int RenderWindow::GetPositionY()
		{
			return m_posY;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetWidth(unsigned int width)
		{
			m_width = width;
		}

		// --------------------------------------------------------------------------------
		inline unsigned int RenderWindow::GetWidth()
		{
			return m_width;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetHeight(unsigned int height)
		{
			m_height = height;
		}

		// --------------------------------------------------------------------------------
		inline unsigned int RenderWindow::GetHeight()
		{
			return m_height;
		}
	} // namespace Render
} // namespace oakvr
