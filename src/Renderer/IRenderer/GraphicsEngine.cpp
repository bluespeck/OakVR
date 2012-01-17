#include <cassert>

#include "GraphicsEngine.h"
#include "RenderWindow.h"
#include "Core/Math/Matrix.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		GraphicsEngine::GraphicsEngine()
		: m_pRenderWindow(nullptr)
		, m_pOrthographicProjectionMatrix(nullptr)
		, m_pPerspectiveProjectionMatrix(nullptr)
		, m_currentPrimitiveTopology(ePT_TriangleList)
		, m_numVerticesPerPrimitive(3)
		, m_pCurrentVertexBuffer(nullptr)
		, m_pCurrentIndexBuffer(nullptr)
		, m_pCurrentVertexShader(nullptr)
		, m_pCurrentPixelShader(nullptr)
		, m_pDebugTextRenderer(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::SetRenderWindow(RenderWindow *pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer)
		{
			m_pDebugTextRenderer = pDebugTextRenderer;
		}

		// --------------------------------------------------------------------------------
		GraphicsEngine::~GraphicsEngine()
		{
			Cleanup();
			m_pRenderWindow = nullptr;	// it should not be the owner of this object
			
			if(m_pOrthographicProjectionMatrix)
				delete m_pOrthographicProjectionMatrix;
			
			if(m_pPerspectiveProjectionMatrix)
				delete m_pPerspectiveProjectionMatrix;
		}

		// --------------------------------------------------------------------------------
		void GraphicsEngine::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			assert(0 && "OutputText not implemented!");
		}
	}	// namespace Render
}	// namespace Oak3D
