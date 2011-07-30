
#include "../../../Oak3DCoreConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

#include "DirectX9DebugText.h"
#include "DirectX9Shader.h"
#include "DirectX9GraphicsEngine.h"
#include "../DirectXUtils.h"

#include "../../../Font.h"
#include "../../../VertexBuffer.h"
#include "../../../Engine.h"
#include "../../../Texture.h"
#include "../../../../Math/Matrix.h"
#include "../../../../Math/Vector3.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		DirectX9DebugText::DirectX9DebugText()
		: m_pFont(nullptr)
		//, m_pVertexShader(nullptr)
		//, m_pPixelShader(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		DirectX9DebugText::~DirectX9DebugText()
		{
			if(m_pFont)
			{
				m_pFont->Release();
				delete m_pFont;
			}
			/*
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
			*/
		}

		// --------------------------------------------------------------------------------
		void DirectX9DebugText::Init()
		{
			DirectX9GraphicsEngine *ge = (DirectX9GraphicsEngine *)Engine::GetInstance()->GetGraphicsEngine();
			HR(D3DXCreateFont(ge->GetDevice(),     //D3D Device
				22,               //Font height
				0,                //Font width
				FW_NORMAL,        //Font Weight
				1,                //MipLevels
				false,            //Italic
				DEFAULT_CHARSET,  //CharSet
				OUT_DEFAULT_PRECIS, //OutputPrecision
				ANTIALIASED_QUALITY, //Quality
				DEFAULT_PITCH|FF_DONTCARE,//PitchAndFamily
				L"Arial",          //pFacename,
				&m_pFont));         //ppFont
			/*
			m_pFont = new Font();
			m_pFont->Initialize(L"../resources/font/DebugFont.index", L"../resources/font/DebugFont.bmp");

			m_pVertexShader = new DirectX9Shader();
			m_pPixelShader = new DirectX9Shader();
			m_pVertexShader->Init( L"../resources/shaders/DebugFont.hlsl", eST_VertexShader, (VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0));
			m_pPixelShader->Init( L"../resources/shaders/DebugFont.hlsl", eST_PixelShader);
			m_pVertexShader->Load();
			m_pPixelShader->Load();
			*/
		}

		// --------------------------------------------------------------------------------
		void DirectX9DebugText::OutputText(const std::wstring &text, uint32_t x, uint32_t y)
		{
			RECT rc = {x, y};
			
			m_pFont->DrawTextW(NULL,        //pSprite
				text.c_str(),  //pString
				-1,          //Count
				&rc,  //pRect
				DT_LEFT|DT_NOCLIP,//Format,
				0xFFFFFFFF); //Color
			/*
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

			DirectX9GraphicsEngine *ge = (DirectX9GraphicsEngine *)Engine::GetInstance()->GetGraphicsEngine();

			ge->UseVertexBuffer( &vb );
			ge->UseShader( m_pVertexShader );
			ge->UseShader( m_pPixelShader );
			ge->UsePrimitiveTopology( ePT_TriangleList );			
			
			ID3D11ShaderResourceView *pSRView = NULL;
			HR(ge->GetDevice()->CreateShaderResourceView((ID3D11Resource *)m_pFont->GetTexture()->GetData(), nullptr, &pSRView ));
			ge->GetDeviceContext()->PSSetShaderResources(0, 1, &pSRView);
			
			// TODO Add code for filling up constant buffers and shader resources
			//ge->DisableDepthBuffer();
			ge->GetDeviceContext()->Draw(numVertices, 0);
			//ge->EnableDepthBuffer();
			*/
		}

	} // namespace Core
} // namespace Oak3D

#endif // OAK3D_DIRECTX_9
