#include "Renderer/Renderer/RenderWindow.h"
#include "Log/Log.h"

namespace oakvr
{
	namespace render
	{
		class RenderWindow::RenderWindowImpl
		{
			uint32_t osHandler;
		};

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow() :
		m_pImpl{new RenderWindowImpl()}
		{
			m_windowState = eWS_Normal;
			m_bFullScreen = false;
			m_osHandle = 0;
			m_posX = m_posY = 0;
			m_width = 1280;
			m_height = 960;
			m_title = "oakvr";
		}

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow( const std::string &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title {title}, m_posX{posX}, m_posY{posY}, m_width{width}, m_height{height}, m_pImpl{new RenderWindowImpl()}
		{

		}

		// --------------------------------------------------------------------------------
		RenderWindow::~RenderWindow()
		{

		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Initialize()
		{
			Log::PrintInfo("RW Initialized!\n");
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

	} // namespace Render
} // namespace oakvr
