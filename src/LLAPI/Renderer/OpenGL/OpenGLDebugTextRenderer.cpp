
#if defined _WIN32
#	include <windows.h>
#	include <wingdi.h>
#endif


#include <string>
#include <fstream>
#include <cassert>
#include <cctype>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <gl/wglext.h>

//#include "ro3d/Engine.h"

#include "OpenGLDebugTextRenderer.h"
#include "OpenGLRenderer.h"
#include "OpenGLShader.h"

//#include "Renderer/IRenderer/Font.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/Texture.h"


#include "Math/Matrix.h"
#include "Math/Vector3.h"

namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		OpenGLDebugTextRenderer::OpenGLDebugTextRenderer()
		: m_pFont(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		OpenGLDebugTextRenderer::~OpenGLDebugTextRenderer()
		{
//			if(m_pFont)
//				delete m_pFont;
		}

		// --------------------------------------------------------------------------------
		void OpenGLDebugTextRenderer::Init()
		{	
/*			m_pFont = new Font();
			m_pFont->Initialize("../resources/font/DebugFont.index", "../resources/font/DebugFont.tga");

			while(!Engine::GetRenderer()->IsInitialized());
			// TODO Different resources from the same file :(((((((((((((((((((( => same id => second resource is not created
			Shader::ShaderAdditionalInitParams params;
			params.shaderType = eST_VertexShader;
			m_pVertexShader = Engine::GetResourceManager()->GetResource<OpenGLShader>("../resources/shaders/glsl/DebugFontVS.glsl", &params);
			params.shaderType = eST_PixelShader;
			m_pFragmentShader = Engine::GetResourceManager()->GetResource<OpenGLShader>("../resources/shaders/glsl/DebugFontPS.glsl", &params);
*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLDebugTextRenderer::OutputText(const std::string &text, uint32_t x, uint32_t y)
		{
/*			if(!m_pFont->GetTexture()->IsReady())
				return;

			Font::TextVertex *pVertices;
			uint32_t numVertices = 0;
			m_pFont->BuildVertexArray(text, (float)x, (float)y, pVertices, numVertices);
		

			// create vertex buffer
			VertexBuffer vb;

			uint32_t vf = VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0;
			vb.Create(numVertices, vf);
						
			void *pData;
			vb.Lock(&pData);
			memcpy( pData, pVertices, sizeof(Font::TextVertex) * numVertices);
			vb.Unlock();

			OpenGLRenderer *ge = (OpenGLRenderer *)Engine::GetInstance()->GetRenderer();

			ro3d::Math::Matrix *pM = ge->GetViewMatrix();
			*pM = ro3d::Math::Matrix::CreateIdentityMatrix();
			ge->UseVertexBuffer( &vb );
			//ge->UseIndexBuffer( nullptr );
			ge->UseTexture(m_pFont->GetTexture());

			ge->UseShader(m_pVertexShader);
			ge->UseShader(m_pFragmentShader);

			ge->DrawPrimitives(numVertices * 3);
			ge->ReleaseVertexBuffer(&vb);
*/
		}

	} // namespace Render
} // namespace ro3d

