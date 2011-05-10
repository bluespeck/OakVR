
//#if defined(OAK3D_WINDOWS) && defined(OAK3D_DIRECTX_11)

#include <D3DX11.h>
#include <D3D11.h>
#include <D3D10.h>
#include <cassert>

#include "DirectX11GraphicsEngine.h"
#include "WindowsRenderWindow.h"

#include "../GraphicsEngineUtils.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Texture.h"


namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		DirectX11GraphicsEngine::DirectX11GraphicsEngine()
		{

		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Initialize()
		{
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());

			// Direct3D initialization

			// Create a struct to hold information about the swap chain
			DXGI_SWAP_CHAIN_DESC scd;

			// Zero out the struct for use
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			// Fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = hWnd;                                // the window to be used
			scd.SampleDesc.Count = 1;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/fullscreen mode
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// allow windowed/fullscreen switch

			// Create a device, device context and swap chain using the information in the scd struct
			HR(D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&m_pSwapChain,
				&m_pDevice,
				NULL,
				&m_pDeviceContext));


			// Set the render target

			// get the address of the back buffer
			ID3D11Texture2D *pBackBufferTexture;
			m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);

			// use the back buffer address to create the render target
			HR(m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pBackBufferRenderTargetView));
			pBackBufferTexture->Release();

			// set the render target as the back buffer
			m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBufferRenderTargetView, NULL);


			// Set the viewport

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (float)m_pRenderWindow->GetWidth();
			viewport.Height = (float)m_pRenderWindow->GetHeight();

			m_pDeviceContext->RSSetViewports(1, &viewport);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Render()
		{			
			m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRenderTargetView, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

			// render 3D stuff to back buffer 

			HR(m_pSwapChain->Present(0, 0));
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Cleanup()
		{
			m_pSwapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

			// Close and release all existing COM objects
			m_pSwapChain->Release();
			m_pBackBufferRenderTargetView->Release();
			m_pDevice->Release();
			m_pDeviceContext->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		void* DirectX11GraphicsEngine::CreateShaderFromFile(const std::wstring &fileName, ShaderType eShaderType)
		{			
			void *pShader = nullptr;

			ID3D10Blob *pShaderByteCode;
			ID3D10Blob *pErrorMsg;

			switch(eShaderType)
			{
			case eST_VertexShader:
				{
					// Compile shader from file
					HR(D3DX11CompileFromFileW(fileName.c_str(), nullptr, nullptr, "VertexShader", "vs_5_0", 0, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr));
					// Create DirectX shader
					HR(m_pDevice->CreateVertexShader(pShaderByteCode->GetBufferPointer(), pShaderByteCode->GetBufferSize(), nullptr, (ID3D11VertexShader **)&pShader));
					break;
				}
			case eST_PixelShader:
				{
					HR(D3DX11CompileFromFileW(fileName.c_str(), nullptr, nullptr, "PixelShader", "ps_5_0", 0, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr));
					HR(m_pDevice->CreatePixelShader(pShaderByteCode->GetBufferPointer(), pShaderByteCode->GetBufferSize(), nullptr, (ID3D11PixelShader **)&pShader));
					break;
				}
			default:
				assert("Shader was not correctly initialized!" && 0);
				return nullptr;
			}

			return pShader;

		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseShader(void *pShader, ShaderType eShaderType)
		{
			if(pShader == nullptr)
				return;

			switch(eShaderType)
			{
			case eST_VertexShader:
				{
					((ID3D11VertexShader *)pShader)->Release();
					break;
				}
			case eST_PixelShader:
				{
					((ID3D11PixelShader *)pShader)->Release();
					break;
				}
			default:
				assert("Shader was not correctly initialized!" && 0);
				return;
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateTexture( Texture *pTexture )
		{
			/*
			ID3D11Texture2D *pDXTexture;

			wchar_t root[100] = L"Data/";
			wcscat( root, pTexture->GetStrId());

			HRESULT hRet;
			
			D3DXIMAGE_INFO imageInfo;

			hRet = D3DXCreateTextureFromFileEx( m_pD3DDevice,
				root,
				texture->GetWidth(),
				texture->GetHeight(),
				3,
				0,
				(D3DFORMAT)texture->GetPixelFormat(),
				D3DPOOL_MANAGED,
				D3DX_FILTER_LINEAR, 
				D3DX_FILTER_LINEAR, 
				0, &imageInfo, NULL, &n_texture );

			if( FAILED(hRet) ) { n_texture->Release(); n_texture = NULL; }

			texture->SetWidth(imageInfo.Width);
			texture->SetHeight(imageInfo.Height);

			texture->m_data = n_texture;
			*/
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseTexture( Texture *texture )
		{
			//((ID3D11Texture2D *)texture->m_pData)->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			//IDirect3DVertexBuffer9 *pVB = NULL;
			//m_pD3DDevice->CreateVertexBuffer( pVertexBuffer->m_count * pVertexBuffer->m_vertexSize , D3DUSAGE_WRITEONLY, pVertexBuffer->m_format, D3DPOOL_MANAGED, &pVB, NULL );

			//pVertexBuffer->m_data = pVB;
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::LockVertexBuffer( VertexBuffer *pVertexBuffer, uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags )
		{	
			//((IDirect3DVertexBuffer9 *)pVertexBuffer->m_data)->Lock( offsetToLock, sizeToLock, ppBuff, flags );	
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			//D3DVERTEXBUFFER_DESC desc;
			//((IDirect3DVertexBuffer9 *)pVertexBuffer->m_data)->GetDesc(&desc);

			//((IDirect3DVertexBuffer9 *)pVertexBuffer->m_data)->Unlock();	
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			//((IDirect3DVertexBuffer9 *)pVertexBuffer->m_data)->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			//IDirect3DIndexBuffer9 *pIB = NULL;

			//m_pD3DDevice->CreateIndexBuffer( pIndexBuffer->m_count * sizeof( DWORD ), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &pIB, NULL );

			//pIndexBuffer->m_data = pIB;
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::LockIndexBuffer( IndexBuffer *pIndexBuffer, uint32_t offsetToLock, uint32_t sizeToLock, void **ppBuff, uint32_t flags )
		{	
			//((IDirect3DIndexBuffer9 *)pIndexBuffer->m_data)->Lock( offsetToLock, sizeToLock, ppBuff, flags );	
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			//((IDirect3DIndexBuffer9 *)pIndexBuffer->m_data)->Unlock();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			//((IDirect3DIndexBuffer9 *)pIndexBuffer->m_data)->Release();
		}

	}	// namespace Core
}	// namespace Oak3D

//#endif
