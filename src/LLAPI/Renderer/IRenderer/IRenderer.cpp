#include <cassert>

#include "IRenderer.h"
#include "RenderWindow.h"
#include "Math/Matrix.h"


namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		IRenderer::IRenderer()
		: m_pRenderWindow(nullptr)
		, m_currentPrimitiveTopology(ePT_TriangleList)
		, m_numVerticesPerPrimitive(3)
		, m_pCurrentVertexBuffer(nullptr)
		, m_pCurrentIndexBuffer(nullptr)
		, m_pCurrentVertexShader(nullptr)
		, m_pCurrentPixelShader(nullptr)
		, m_pDebugTextRenderer(nullptr)
		, m_bInitialized(false)
		{
			Math::Matrix identityMatrix = Math::Matrix::CreateIdentityMatrix();
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			m_pWorldMatrix = new Math::Matrix();			
			m_pViewMatrix = new Math::Matrix();
			*m_pPerspectiveProjectionMatrix = identityMatrix;
			*m_pOrthographicProjectionMatrix = identityMatrix;
			*m_pWorldMatrix = identityMatrix;
			*m_pViewMatrix = identityMatrix;
				
		}

		// --------------------------------------------------------------------------------
		void IRenderer::SetRenderWindow(RenderWindow *pRenderWindow)
		{
			m_pRenderWindow = pRenderWindow;
		}

		// --------------------------------------------------------------------------------
		void IRenderer::SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer)
		{
			m_pDebugTextRenderer = pDebugTextRenderer;
		}

		// --------------------------------------------------------------------------------
		IRenderer::~IRenderer()
		{
			Cleanup();
			m_pRenderWindow = nullptr;	// it should not be the owner of this object
			
			if(m_pOrthographicProjectionMatrix)
				delete m_pOrthographicProjectionMatrix;
			
			if(m_pPerspectiveProjectionMatrix)
				delete m_pPerspectiveProjectionMatrix;
		}

		// --------------------------------------------------------------------------------
		void IRenderer::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			assert(0 && "OutputText not implemented!");
		}
	}	// namespace Render
}	// namespace ro3d
