
//#if defined(OAK3D_WINDOWS) && defined(OAK3D_DIRECTX_11)

#include <D3DX11.h>
#include <D3D11.h>
#include <D3D10.h>
#include <cassert>

#include "DirectX11GraphicsEngine.h"
#include "WindowsRenderWindow.h"
#include "DirectXUtils.h"

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
			ID3D11Resource *pTex;
			const std::wstring &path = pTexture->GetId().GetStrId();
			D3DX11_IMAGE_LOAD_INFO ili;
			HR(D3DX11CreateTextureFromFileW(m_pDevice, path.c_str(), &ili, nullptr, &pTex, nullptr));
			
			// store created texture in our container
			pTexture->SetData(pTex);

			// fill texture properties
			pTexture->SetWidth(ili.Width);
			pTexture->SetHeight(ili.Height);

			switch(ili.Format)
			{
			case DXGI_FORMAT_B8G8R8A8_UNORM:
				pTexture->SetFormat(Texture::eTF_R8G8B8A8_UNORM);
				break;
			case DXGI_FORMAT_B8G8R8X8_UNORM:
				pTexture->SetFormat(Texture::eTF_R8G8B8X8_UNORM);
				break;
			case DXGI_FORMAT_R8G8B8A8_UINT:
				pTexture->SetFormat(Texture::eTF_R8G8B8A8_UINT);
				break;
			default:
				pTexture->SetFormat(Texture::eTF_UNKNOWN);
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseTexture( Texture *pTexture )
		{
			((ID3D11Resource *)pTexture->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			D3D11_BUFFER_DESC desc;
			ID3D11Buffer *pVB = NULL;
			desc.ByteWidth = pVertexBuffer->GetVertexCount() * pVertexBuffer->GetVertexSize();
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = pVertexBuffer->GetVertexSize();
			desc.Usage = D3D11_USAGE_DYNAMIC;

			m_pDevice->CreateBuffer(&desc, NULL, &pVB);
			pVertexBuffer->SetData(pVB);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			// no offset??
			D3D11_MAPPED_SUBRESOURCE ms;
			m_pDeviceContext->Map((ID3D11Resource *)pVertexBuffer->GetData(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			*ppBuff = ms.pData;
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			m_pDeviceContext->Unmap((ID3D11Resource *)pVertexBuffer->GetData(), NULL);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			((ID3D11Resource *)pVertexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			D3D11_BUFFER_DESC desc;
			ID3D11Buffer *pIB = NULL;
			desc.ByteWidth = pIndexBuffer->GetIndexCount() * pIndexBuffer->GetIndexSize();
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = pIndexBuffer->GetIndexSize();
			desc.Usage = D3D11_USAGE_DYNAMIC;

			m_pDevice->CreateBuffer(&desc, NULL, &pIB);
			pIndexBuffer->SetData(pIB);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			// no offset?
			D3D11_MAPPED_SUBRESOURCE ms;
			m_pDeviceContext->Map((ID3D11Resource *)pIndexBuffer->GetData(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			m_pDeviceContext->Unmap((ID3D11Resource *)pIndexBuffer->GetData(), 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			((ID3D11Resource *)pIndexBuffer->GetData())->Release();
		}

	}	// namespace Core
}	// namespace Oak3D

//#endif
