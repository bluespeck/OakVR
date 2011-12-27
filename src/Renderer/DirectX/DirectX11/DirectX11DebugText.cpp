
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

#include "Oak3D/Engine.h"

#include "DirectX11DebugText.h"
#include "DirectX11Shader.h"
#include "DirectX11GraphicsEngine.h"
#include "Renderer/DirectX/DirectXUtils.h"

#include "Renderer/IRenderer/Font.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/Texture.h"

#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"

namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX11DebugText::DirectX11DebugText()
		: m_pFont(nullptr)
		, m_pVertexShader(nullptr)
		, m_pPixelShader(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		DirectX11DebugText::~DirectX11DebugText()
		{
			if(m_pFont)
				delete m_pFont;
			if(m_pPixelShader)
			{
				m_pPixelShader->Release();
				delete m_pPixelShader;
				m_pPixelShader = nullptr;
			}
			if(m_pVertexShader)
			{
				m_pVertexShader->Release();
				delete m_pVertexShader;
				m_pVertexShader = nullptr;
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11DebugText::Init()
		{	
			m_pFont = new Font();
			m_pFont->Initialize("../resources/font/DebugFont.index", "../resources/font/DebugFont.dds");

			m_pVertexShader = new DirectX11Shader();
			m_pPixelShader = new DirectX11Shader();
			m_pVertexShader->Init( "../resources/shaders/DebugFont.hlsl", eST_VertexShader, (VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0));
			m_pPixelShader->Init( "../resources/shaders/DebugFont.hlsl", eST_PixelShader);
			m_pVertexShader->Load();
			m_pPixelShader->Load();
		}

		// --------------------------------------------------------------------------------
		void DirectX11DebugText::OutputText(const std::string &text, uint32_t x, uint32_t y)
		{
			if(!m_pFont->GetTexture()->IsReady())
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

			DirectX11GraphicsEngine *ge = (DirectX11GraphicsEngine *)Engine::GetInstance()->GetGraphicsEngine();

			ge->UseVertexBuffer( &vb );
			ge->UseShader( m_pVertexShader );
			ge->UseShader( m_pPixelShader );
			ge->UsePrimitiveTopology( ePT_TriangleList );			
			
			ID3D11ShaderResourceView *pSRView = nullptr;
			HR(ge->GetDevice()->CreateShaderResourceView((ID3D11Resource *)m_pFont->GetTexture()->GetData(), nullptr, &pSRView ));
			ge->GetDeviceContext()->PSSetShaderResources(0, 1, &pSRView);
			
			ge->DisableDepthBuffer();
			ge->GetDeviceContext()->Draw(numVertices, 0);
			ge->EnableDepthBuffer();
		}

	} // namespace Render
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_11
