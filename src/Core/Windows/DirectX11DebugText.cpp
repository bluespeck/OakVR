
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

#include "DirectX11DebugText.h"
#include "DirectX11Shader.h"
#include "DirectX11GraphicsEngine.h"

#include "../Font.h"
#include "../VertexBuffer.h"
#include "../Engine.h"

namespace Oak3D
{
	namespace Core
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
			m_pFont->Initialize(L"../resources/font/DebugFont.index", L"../resources/font/DebugFont.bmp");

			m_pVertexShader = new DirectX11Shader();
			m_pPixelShader = new DirectX11Shader();
			m_pVertexShader->Init( L"../resources/shaders/DebugFont.hlsl", eST_VertexShader);
			m_pPixelShader->Init( L"../resources/shaders/DebugFont.hlsl", eST_PixelShader);
			m_pVertexShader->Load();
			m_pPixelShader->Load();
		}

		// --------------------------------------------------------------------------------
		void DirectX11DebugText::OutputText(const std::wstring &text, uint32_t x, uint32_t y)
		{
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

			// Create input layout
			void *pLayoutDesc;
			uint32_t numElems;

			ge->CreateInputLayoutDesc(vb.GetVertexFormat(), pLayoutDesc, numElems);
			// TODO find a way to create input layout here

			// fill constant buffers
			D3D11_BUFFER_DESC constantBufferDesc;
			D3D11_SAMPLER_DESC samplerDesc;
			D3D11_BUFFER_DESC pixelBufferDesc;

			struct ConstantBufferType
			{
				D3DXMATRIX world;
				D3DXMATRIX view;
				D3DXMATRIX projection;
			};

			// Setup the description of the dynamic constant buffer that is in the vertex shader.
			constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
			constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			constantBufferDesc.MiscFlags = 0;
			constantBufferDesc.StructureByteStride = 0;

			
			
		}

	} // namespace Core
} // namespace Oak3D