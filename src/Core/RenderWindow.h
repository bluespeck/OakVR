
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDERWINDOW_H__
#define __OAK3D_INCLUDE_RENDERWINDOW_H__

#include <string>
namespace Oak3D
{
	namespace Core
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

			inline void SetOSHandle( long int handle );
			inline long int GetOSHandle();
			
			inline void SetPositionX( int posX );
			inline int GetPositionX();

			inline void SetPositionY( int posY );
			inline int GetPositionY();

			inline void SetWidth( unsigned int width );
			inline unsigned int GetWidth();
			
			inline void SetHeight( unsigned int height );
			inline unsigned int GetHeight();
						
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
	}
}

#include "RenderWindow.hpp"

#endif
