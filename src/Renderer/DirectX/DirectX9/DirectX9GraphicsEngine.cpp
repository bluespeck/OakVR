
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <cassert>

#include "Oak3D/Engine.h"

#include "Renderer/DirectX/DirectXUtils.h"
#include "DirectX9GraphicsEngine.h"
#include "DirectX9DebugText.h"
#include "DirectX9Shader.h"

#include "Renderer/IRenderer/WindowsRenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngineUtils.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Texture.h"
#include "Core/Math/Matrix.h"

namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX9GraphicsEngine::DirectX9GraphicsEngine()
		: m_pDevice(nullptr)
		, m_pDebugText(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::Initialize()
		{
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			SetWindowTextW(hWnd, L"Oak3D [DX9]");
			/////
			// create Direct3D device

			LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

			D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

			ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
			d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //disable vsync
			d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D

			// create a device class using this information and information from the d3dpp stuct
			d3d->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pDevice);

			/////
			// set the render target

			// get the address of the back buffer
			//m_pDevice->GetBackBuffer(0, 0,, &m_pRenderTarget);

			/////
			// set the viewport

			D3DVIEWPORT9 viewport;
			ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));

			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = m_pRenderWindow->GetWidth();
			viewport.Height = m_pRenderWindow->GetHeight();
			viewport.MinZ = 0;
			viewport.MaxZ = 1000;

			m_pDevice->SetViewport(&viewport);

			/////
			// create projection matrices
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			D3DXMatrixPerspectiveFovLH((D3DXMATRIX *)(void *)m_pPerspectiveProjectionMatrix, 3.141592f * 0.25f, 1.25f, 1, 1000);
			D3DXMatrixOrthoLH((D3DXMATRIX *)(void *)m_pOrthographicProjectionMatrix, (float)viewport.Width, (float)viewport.Height, 0, 1000);

			/////
			// initialize debug text
			m_pDebugText = new DirectX9DebugText();
			m_pDebugText->Init();
			
			InitializeStateObjects();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::InitializeStateObjects()
		{
			
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::Render()
		{	
			// clear the window to a deep blue
			m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f), 1.0f, 0);

			m_pDevice->BeginScene();

			// render 3D stuff to back buffer

			char str[128];
			sprintf(str, "FPS: %.0f", (1.0f / Oak3D::Engine::GetTimer()->GetDeltaTime()));
			m_pDebugText->OutputText(str, 10, 10);

			m_pDevice->EndScene();

			m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::Cleanup()
		{
			delete m_pDebugText;

			m_pDevice->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::CreateShader(Shader *pShader)
		{
			DirectX9Shader *pSh = static_cast<DirectX9Shader *>(pShader);
			switch(pSh->GetType())
			{
			case eST_VertexShader:
				{
					LPD3DXBUFFER pShaderByteCode = nullptr;
					LPD3DXBUFFER pErrorMsg = nullptr;
					// compile vertex shader from file
					HR_ERR(D3DXCompileShaderFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakVertexShader", "vs_2_0", 0, &pShaderByteCode, &pErrorMsg, nullptr), pErrorMsg);
					
					// create DirectX vertex shader
					if(pShaderByteCode)
					{
						IDirect3DVertexShader9 *pCompiledShader = nullptr;
						m_pDevice->CreateVertexShader((DWORD *)pShaderByteCode->GetBufferPointer(), &pCompiledShader);
						pSh->SetCompiledShader(pCompiledShader);

						// create input layout
						void *pLayoutDesc = nullptr;
						uint32_t numElems;
						CreateInputLayoutDesc(pSh->GetVertexFormat(), pLayoutDesc, numElems);						
						D3DVERTEXELEMENT9 * pld = (D3DVERTEXELEMENT9 *)pLayoutDesc;
						IDirect3DVertexDeclaration9 *pInputLayout = nullptr;
						HR(m_pDevice->CreateVertexDeclaration(pld, &pInputLayout));
						pSh->SetInputLayout(pInputLayout);

						return ;
					}
					break;
				}
			case eST_PixelShader:
				{
					LPD3DXBUFFER pShaderByteCode = nullptr;
					LPD3DXBUFFER pErrorMsg = nullptr;
					// compile pixel shader from file
					HR(D3DXCompileShaderFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakPixelShader", "ps_2_0", 0, &pShaderByteCode, &pErrorMsg, nullptr));
					IDirect3DPixelShader9 *pCompiledShader = nullptr;
					// create DirectX pixel shader
					if(pShaderByteCode)
					{
						m_pDevice->CreatePixelShader((DWORD *)pShaderByteCode->GetBufferPointer(), &pCompiledShader);
						pSh->SetCompiledShader(pCompiledShader);

						return;
					}
					break;
				}
			default:
				assert("Shader was not correctly initialized!" && 0);
			}
			pShader->SetCompiledShader(nullptr);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::ReleaseShader(Shader *pShader)
		{
			if(pShader == nullptr)
				return;
			((IDirect3DResource9 *)pShader->GetCompiledShader())->Release();
			pShader->SetCompiledShader(nullptr);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::CreateTexture( Texture *pTexture )
		{
			IDirect3DTexture9 *pTex;
			const std::string path = pTexture->GetId().GetStrId();
			D3DXIMAGE_INFO ili;
			
			HR(D3DXGetImageInfoFromFileA(path.c_str(), &ili));
			HR(D3DXCreateTextureFromFileA(m_pDevice, path.c_str(), &pTex));
			
			// store created texture in our container
			pTexture->SetData(pTex);

			// fill texture properties
			pTexture->SetWidth(ili.Width);
			pTexture->SetHeight(ili.Height);

			switch(ili.Format)
			{
			case D3DFMT_A8R8G8B8:
				pTexture->SetFormat(Texture::eTF_A8R8G8B8_UINT);
				break;
			case D3DFMT_X8R8G8B8:
				pTexture->SetFormat(Texture::eTF_X8R8G8B8_UINT);
				break;
			default:
				pTexture->SetFormat(Texture::eTF_UNKNOWN);
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::ReleaseTexture( Texture *pTexture )
		{
			((IDirect3DResource9 *)pTexture->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			IDirect3DVertexBuffer9 *pVB = NULL;
			unsigned int length = pVertexBuffer->GetVertexCount() * pVertexBuffer->GetVertexSize();
			
			HR(m_pDevice->CreateVertexBuffer(length, D3DUSAGE_SOFTWAREPROCESSING, 0, D3DPOOL_DEFAULT, &pVB, nullptr));
			pVertexBuffer->SetData(pVB);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			// no offset??
			((IDirect3DVertexBuffer9 *)pVertexBuffer->GetData())->Lock(offsetToLock, sizeToLock, ppBuff, 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			((IDirect3DVertexBuffer9 *)pVertexBuffer)->Unlock();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			((IDirect3DVertexBuffer9 *)pVertexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			IDirect3DIndexBuffer9 *pIB = NULL;
			
			m_pDevice->CreateIndexBuffer(pIndexBuffer->GetIndexCount() * pIndexBuffer->GetIndexSize(), D3DUSAGE_DYNAMIC, pIndexBuffer->GetIndexSize() == 2? D3DFMT_INDEX16: D3DFMT_INDEX32, D3DPOOL_DEFAULT, &pIB, nullptr);
			pIndexBuffer->SetData(pIB);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Lock(offsetToLock, sizeToLock, ppBuff, 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Unlock();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			m_pDebugText->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{			
			D3DVERTEXELEMENT9 layout[12];
			numElems = 0;
			int offset = 0;
			if(vertexFormat & VertexBuffer::eVF_XYZ)
			{
				layout[numElems].Usage = D3DDECLUSAGE_POSITION;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT3;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 12;
				++numElems;
			}
			if(vertexFormat & VertexBuffer::eVF_Normal)
			{
				layout[numElems].Usage = D3DDECLUSAGE_NORMAL;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT3;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 12;
				++numElems;
			}
			if(vertexFormat & VertexBuffer::eVF_Diffuse)
			{
				layout[numElems].Usage = D3DDECLUSAGE_COLOR;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type= D3DDECLTYPE_D3DCOLOR;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 16;
				++numElems;
			}

			if(vertexFormat & VertexBuffer::eVF_Tex0)
			{
				layout[numElems].Usage = D3DDECLUSAGE_TEXCOORD;
				layout[numElems].UsageIndex = 0;
				layout[numElems].Type = D3DDECLTYPE_FLOAT2;
				layout[numElems].Stream = 0;
				layout[numElems].Offset = offset;
				layout[numElems].Method = D3DDECLMETHOD_DEFAULT;
				offset += 8;
				++numElems;
			}

			pLayoutDesc = new D3DVERTEXELEMENT9[numElems];
			memcpy(pLayoutDesc, layout, numElems * sizeof(D3DVERTEXELEMENT9));			
		}


		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			IDirect3DVertexBuffer9 *pBuffer = (IDirect3DVertexBuffer9 *)pVertexBuffer->GetData();
			uint32_t stride = pVertexBuffer->GetVertexSize();
			uint32_t offset = 0;
			m_pDevice->SetStreamSource(0, pBuffer, offset, stride);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			IDirect3DIndexBuffer9 *pBuffer = (IDirect3DIndexBuffer9 *)pIndexBuffer->GetData();
			m_pDevice->SetIndices(pBuffer);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			// Not available
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::UseShader( Shader *pShader )
		{
			
			if(pShader->GetType() == eST_VertexShader)
			{
				IDirect3DVertexShader9 *pVertexShader = (IDirect3DVertexShader9 *) pShader->GetCompiledShader();
				m_pDevice->SetVertexDeclaration( ((DirectX9Shader*)pShader)->GetInputLayout() );
			}
			else
			{
				IDirect3DPixelShader9 *pPixelShader = (IDirect3DPixelShader9 *) pShader->GetCompiledShader();
				m_pDevice->SetPixelShader(pPixelShader);
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::EnableDepthBuffer()
		{
			m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		}

		// --------------------------------------------------------------------------------
		void DirectX9GraphicsEngine::DisableDepthBuffer()
		{
			m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		}

	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_9
