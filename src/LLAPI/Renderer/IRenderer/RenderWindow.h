#pragma once

#include <string>
namespace ro3d
{
	namespace Render
	{
		class RenderWindow
		{
		public:
			RenderWindow();
			RenderWindow( const std::wstring &title, int posX, int posY, unsigned int width, unsigned int height);
			
			virtual void Initialize() = 0;
			virtual void Minimize() = 0;
			virtual void Maximize() = 0;
			virtual void RestoreSize() = 0;
			virtual void Refresh() = 0;

			virtual void SetOSHandle( long int handle );
			virtual long int GetOSHandle();
			
			virtual void SetPositionX( int posX );
			virtual int GetPositionX();

			virtual void SetPositionY( int posY );
			virtual int GetPositionY();

			virtual void SetWidth( unsigned int width );
			virtual unsigned int GetWidth();
			
			inline void SetHeight( unsigned int height );
			inline unsigned int GetHeight();

			virtual const std::wstring &GetTitle(){ return m_title; }
			virtual void SetTitle(const std::wstring &title) { m_title = title; }
						
		protected:

			enum WindowState
			{
				eWS_Normal,
				eWS_Minimized,
				eWS_Maximized
			};

			std::wstring m_title;
			int m_posX, m_posY;
			unsigned int m_width, m_height;
			bool m_bFullScreen;
			WindowState m_windowState;
			
			long int m_osHandle;			
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
} // namespace ro3d
