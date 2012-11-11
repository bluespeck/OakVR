
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>


//#include "Oak3D/Engine.h"

#include "DirectX11DebugTextRenderer.h"
#include "DirectX11Shader.h"
#include "DirectX11Renderer.h"
#include "Renderer/DirectX/DirectXUtils.h"

//#include "Renderer/IRenderer/Font.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/Texture.h"

#include "Math/Matrix.h"
#include "Math/Vector3.h"

namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX11DebugTextRenderer::DirectX11DebugTextRenderer()
		: m_pFont(nullptr)
		, m_pVertexShader(nullptr)
		, m_pPixelShader(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		DirectX11DebugTextRenderer::~DirectX11DebugTextRenderer()
		{
//			if(m_pFont)
//				delete m_pFont;
			if(m_pPixelShader)
			{
//				Oak3D::Engine::GetResourceManager()->ReleaseResource(m_pPixelShader);
				m_pPixelShader = nullptr;
			}
			if(m_pVertexShader)
			{
//				Oak3D::Engine::GetResourceManager()->ReleaseResource(m_pVertexShader);
				m_pVertexShader = nullptr;
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11DebugTextRenderer::Init()
		{	
/*			m_pFont = new Font();
			m_pFont->Initialize("../resources/font/DebugFont.index", "../resources/font/DebugFont.dds");

			DirectX11Shader::ShaderAdditionalInitParams params;
			params.shaderType = eST_VertexShader;
			m_pVertexShader = Oak3D::Engine::GetResourceManager()->GetResource<DirectX11Shader>( "../resources/shaders/hlsl_4_0/DebugFontVS.hlsl", &params);
			params.shaderType = eST_PixelShader;
			m_pPixelShader = Oak3D::Engine::GetResourceManager()->GetResource<DirectX11Shader>( "../resources/shaders/hlsl_4_0/DebugFontPS.hlsl", &params);
*/
		}

		// --------------------------------------------------------------------------------
		void DirectX11DebugTextRenderer::OutputText(const std::string &text, uint32_t x, uint32_t y)
		{
/*			if(!m_pFont->GetTexture()->IsReady() || !m_pVertexShader->IsReady() || !m_pPixelShader->IsReady())
			{
				printf("Font is not yet initialised!");
				return;
			}

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

			DirectX11Renderer *ge = (DirectX11Renderer *)Engine::GetInstance()->GetRenderer();

			ge->UseVertexBuffer( &vb );
			ge->UseShader( m_pVertexShader );
			ge->UseShader( m_pPixelShader );
			ge->UseTexture(m_pFont->GetTexture());
			ge->UsePrimitiveTopology( ePT_TriangleList );		
			
			ge->DisableDepthBuffer();
			ge->DrawPrimitives(numVertices / 3);
			ge->EnableDepthBuffer();
			vb.Release();
*/
		}

	} // namespace Render
} // namespace Oak3D
