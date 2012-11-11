
#include "RenderWindow.h"

namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow()
		{
			m_windowState = eWS_Normal;
			m_bFullScreen = false;
			m_osHandle = 0;
			m_posX = m_posY = 0;
			m_width = 1280;
			m_height = 960;
			m_title = L"ro3d";
		}

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow( const std::wstring &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title(title), m_posX(posX), m_posY(posY), m_width(width), m_height(height)
		{
		}

	}	// namespace Render
}	// namespace ro3d
