#include "GraphicsEngine.h"
#include "RenderWindow.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		GraphicsEngine::GraphicsEngine()
		:m_pRenderWindow(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::SetRenderWindow(RenderWindow *pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		GraphicsEngine::~GraphicsEngine()
		{
			Cleanup();
			m_pRenderWindow = nullptr;
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::OutputText( const std::wstring &text, uint32_t x, uint32_t y)
		{
		}
	}
}
