#include "GraphicsEngine.h"
#include "RenderWindow.h"

namespace Oak3D
{
	namespace Core
	{
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
		void* GraphicsEngine::CreateShaderFromFile(const std::wstring &, ShaderType)
		{
			return nullptr;
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::ReleaseShader( void *, ShaderType)
		{
		}
	}
}
