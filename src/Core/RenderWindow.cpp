
#include "RenderWindow.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow()
		{
			m_windowState = eWS_Normal;
			m_bFullScreen = false;
			m_osHandle = 0;
			m_posX = m_posY = 0;
			m_width = 800;
			m_height = 600;
		}

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow( const std::wstring &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title(title), m_posX(posX), m_posY(posY), m_width(width), m_height(height)
		{			
		}

	}	// namespace Core
}	// namespace Oak3D
