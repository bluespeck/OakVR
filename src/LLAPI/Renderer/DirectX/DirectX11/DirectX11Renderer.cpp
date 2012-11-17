
// include the Direct3D Library files
#pragma comment (lib, "d3d11.lib")


#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>

#include <D3Dcompiler.h>
#include <D3D11Shader.h>
#include <vector>

#include <cassert>

#include "Renderer/DirectX/DirectXUtils.h"



#include "DirectX11Renderer.h"
#include "DirectX11DebugTextRenderer.h"
#include "DirectX11Shader.h"

#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/RendererUtils.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Texture.h"
#include "Renderer/IRenderer/Color.h"
#include "Math/Matrix.h"

#include "Time/Timer.h"



namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX11Renderer::DirectX11Renderer()
		: m_pDevice(nullptr)
		, m_pSwapChain(nullptr)
		, m_pDeviceContext(nullptr)
		, m_pDepthStencilStateDepthEnabled(nullptr)
		, m_pDepthStencilStateDepthDisabled(nullptr)
		, m_bPerspectiveProjection(true)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::Initialize()
		{
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			SetWindowTextW(hWnd, L"ro3d [DX11]");
			/////
			// create Direct3D device, device context and swap chain using the information in the scd struct
						
			DXGI_SWAP_CHAIN_DESC scd;
			
			memset(&scd, 0, sizeof(scd));
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = hWnd;                                // the window to be used
			scd.SampleDesc.Count = 1;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/fullscreen mode
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// allow windowed/fullscreen switch
			D3D_FEATURE_LEVEL featLevel[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1
			};

//			HR(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 
//				0, featLevel, 6, D3D11_SDK_VERSION, &scd, &m_pSwapChain,	&m_pDevice,	nullptr, &m_pDeviceContext));
			
			/////
			// set the render target

			// get the address of the back buffer
			ID3D11Texture2D *pBackBufferTexture;
			m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);

			// use the back buffer address to create the render target

			m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pBackBufferRenderTargetView);
			//pBackBufferTexture->Release();


			// Create the depth/stencil buffer and view.
			D3D11_TEXTURE2D_DESC depthStencilDesc;
	
			depthStencilDesc.Width     = m_pRenderWindow->GetWidth();
			depthStencilDesc.Height    = m_pRenderWindow->GetHeight();
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count   = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0; 
			depthStencilDesc.MiscFlags      = 0;

			ID3D11Texture2D *pDepthStencilBuffer = NULL;
			m_pDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer);
			m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, 0, &m_pDepthStencilView);

			// set the render target as the back buffer
			m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBufferRenderTargetView, NULL);


			InitializeStateObjects();

			m_bInitialized = true;
		}

		// --------------------------------------------------------------------------------
		ro3d::Math::Matrix DirectX11Renderer::CreateViewMatrix(ro3d::Math::Vector3 eye, ro3d::Math::Vector3 lookAt, ro3d::Math::Vector3 up)
		{
			ro3d::Math::Matrix mat;
//			D3DXMatrixLookAtLH((D3DXMATRIX *)&mat, (D3DXVECTOR3 *)&eye, (D3DXVECTOR3 *)&lookAt, (D3DXVECTOR3 *)&up);
			return mat;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::InitializeStateObjects()
		{
			/////
			// set the viewport

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (float)m_pRenderWindow->GetWidth();
			viewport.Height = (float)m_pRenderWindow->GetHeight();
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			m_pDeviceContext->RSSetViewports(1, &viewport);

			/////
			// create projection matrices
			ro3d::Math::Vector3 eye(10.0f, 10.0f, -1.f);
			ro3d::Math::Vector3 lookAt(0.0f, 0.0f, 0.0f);
			ro3d::Math::Vector3 up(0.0f, 1.0f, 0.0f);

//			D3DXMatrixLookAtLH((D3DXMATRIX *)(void *)m_pViewMatrix, (D3DXVECTOR3 *)(void *)&eye, (D3DXVECTOR3 *)(void *)&lookAt, (D3DXVECTOR3 *)(void *)&up);
//			D3DXMatrixPerspectiveFovLH((D3DXMATRIX *)(void *)m_pPerspectiveProjectionMatrix, (3.141592f / 4.f), (viewport.Width / viewport.Height), 1.f, 1000.0f);
//			D3DXMatrixOrthoLH((D3DXMATRIX *)(void *)m_pOrthographicProjectionMatrix, viewport.Width, viewport.Height, .1f, 1000.0f);
			
			/////
			// create shader matrix buffer
			D3D11_BUFFER_DESC mbdesc;
			memset(&mbdesc, 0, sizeof(D3D11_BUFFER_DESC));
			mbdesc.ByteWidth = 3 * sizeof(ro3d::Math::Matrix);
			mbdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			mbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			mbdesc.Usage = D3D11_USAGE_DYNAMIC;
			HR(m_pDevice->CreateBuffer(&mbdesc, nullptr, &m_pMatrixBuffer));
			
			/////
			// create sampler state
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0;
			samplerDesc.MaxAnisotropy = 16;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
			samplerDesc.BorderColor[0] = 0.0f;
			samplerDesc.BorderColor[1] = 0.0f;
			samplerDesc.BorderColor[2] = 0.0f;
			samplerDesc.BorderColor[3] = 0.0f;
			samplerDesc.MinLOD = 0.0f;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
			m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);

			/////
			// create depth stencil states

			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			
			m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilStateDepthEnabled);
			depthStencilDesc.DepthEnable = false;
			HR(m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilStateDepthDisabled));

			/////
			// create rasterizer states
			
			D3D11_RASTERIZER_DESC rasterizerDesc;
			rasterizerDesc.AntialiasedLineEnable = false;
			rasterizerDesc.DepthBias = 0;
			rasterizerDesc.DepthBiasClamp = 0.0f;
			rasterizerDesc.DepthClipEnable = true;
			rasterizerDesc.MultisampleEnable = false;
			rasterizerDesc.ScissorEnable = false;
			rasterizerDesc.SlopeScaledDepthBias = 0.0f;

			rasterizerDesc.FillMode = D3D11_FILL_SOLID;
			rasterizerDesc.CullMode = D3D11_CULL_BACK;
			rasterizerDesc.FrontCounterClockwise = false;

			// create the rasterizer state from the description we just filled out.
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillSolid_CullBack_FrontCW]));
			rasterizerDesc.FrontCounterClockwise = true;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillSolid_CullBack_FrontCCW]));
			rasterizerDesc.FrontCounterClockwise = false;
			rasterizerDesc.CullMode = D3D11_CULL_FRONT;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillSolid_CullFront_FrontCW]));
			rasterizerDesc.FrontCounterClockwise = true;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillSolid_CullFront_FrontCCW]));

			rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
			rasterizerDesc.CullMode = D3D11_CULL_BACK;
			rasterizerDesc.FrontCounterClockwise = false;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillWireframe_CullBack_FrontCW]));
			rasterizerDesc.FrontCounterClockwise = true;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillWireframe_CullBack_FrontCCW]));
			rasterizerDesc.FrontCounterClockwise = false;
			rasterizerDesc.CullMode = D3D11_CULL_FRONT;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillWireframe_CullFront_FrontCW]));
			rasterizerDesc.FrontCounterClockwise = true;
			HR(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerStates[eRSI_FillWireframe_CullFront_FrontCCW]));
			
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::ClearBackground(const Color &color)
		{
			m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRenderTargetView, color);
			m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView ,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::BeginDraw()
		{

		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EndDraw()
		{

		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::SwapBuffers()
		{
			HR(m_pSwapChain->Present(0, 0));
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::Cleanup()
		{
			m_pSwapChain->SetFullscreenState(FALSE, nullptr);    // switch to windowed mode

			// Close and release all existing COM objects
			m_pSwapChain->Release();
			m_pBackBufferRenderTargetView->Release();
			m_pDeviceContext->Release();
			m_pDevice->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		HRESULT CreateInputLayoutDescFromVertexShaderSignature( ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout )
		{
			// Reflect shader info
			ID3D11ShaderReflection* pVertexShaderReflection = nullptr;	
			if ( FAILED( D3DReflect( pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pVertexShaderReflection ) ) ) 
			{
				return S_FALSE;
			}

			// Get shader info
			D3D11_SHADER_DESC shaderDesc;
			pVertexShaderReflection->GetDesc( &shaderDesc );

			// Read input layout description from shader info
			uint32_t byteOffset = 0;
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
			for ( uint32_t i = 0; i< shaderDesc.InputParameters; ++i )
			{
				D3D11_SIGNATURE_PARAMETER_DESC paramDesc;		
				pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc );

				// fill out input element desc
				D3D11_INPUT_ELEMENT_DESC elementDesc;	
				elementDesc.SemanticName = paramDesc.SemanticName;		
				elementDesc.SemanticIndex = paramDesc.SemanticIndex;
				elementDesc.InputSlot = 0;
				elementDesc.AlignedByteOffset = byteOffset;
				elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDesc.InstanceDataStepRate = 0;	

				// determine DXGI format
				if ( paramDesc.Mask == 1 )
				{
					if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32_UINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32_SINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
					byteOffset += 4;
				}
				else if ( paramDesc.Mask <= 3 )
				{
					if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
					byteOffset += 8;
				}
				else if ( paramDesc.Mask <= 7 )
				{
					if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
					byteOffset += 12;
				}
				else if ( paramDesc.Mask <= 15 )
				{
					if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
					else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					byteOffset += 16;
				}

				//save element desc
				inputLayoutDesc.push_back(elementDesc);
			}		

			// Try to create Input Layout
			HRESULT hr = pD3DDevice->CreateInputLayout( &inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout );

			//Free allocation shader reflection memory
			pVertexShaderReflection->Release();
			return hr;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::CreateShader(Shader *pShader)
		{
			DirectX11Shader *pSh = static_cast<DirectX11Shader *>(pShader);
			switch(pSh->GetType())
			{
			case eST_VertexShader:
				{
					ID3D10Blob *pShaderByteCode = nullptr;
					ID3D10Blob *pErrorMsg = nullptr;
					// compile vertex shader from file
//					HR_ERR(D3DX11CompileFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr), pErrorMsg);
					// create DirectX vertex shader
					if(pShaderByteCode)
					{
						ID3D11VertexShader *pCompiledShader = nullptr;
						HR(m_pDevice->CreateVertexShader(pShaderByteCode->GetBufferPointer(), pShaderByteCode->GetBufferSize(), nullptr, &pCompiledShader));
						pSh->SetCompiledShader(pCompiledShader);

						// create input layout (from the compiled shader)						
						ID3D11InputLayout *pInputLayout = nullptr;
						HR(CreateInputLayoutDescFromVertexShaderSignature(pShaderByteCode, m_pDevice, &pInputLayout));
						pSh->SetInputLayout(pInputLayout);
						pShaderByteCode->Release();
						return ;
					}
					break;
				}
			case eST_PixelShader:
				{
					ID3D10Blob *pShaderByteCode = nullptr;
					ID3D10Blob *pErrorMsg = nullptr;
					// compile pixel shader from file
//					HR_ERR(D3DX11CompileFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakPixelShader", "ps_4_0", 0, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr), pErrorMsg);
					ID3D11PixelShader *pCompiledShader = nullptr;
					// create directx pixel shader
					if(pShaderByteCode)
					{
						HR(m_pDevice->CreatePixelShader(pShaderByteCode->GetBufferPointer(), pShaderByteCode->GetBufferSize(), nullptr, &pCompiledShader));
						pSh->SetCompiledShader(pCompiledShader);

						pShaderByteCode->Release();
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
		void DirectX11Renderer::ReleaseShader(Shader *pShader)
		{
			if(pShader == nullptr)
				return;
			((ID3D11Resource *)pShader->GetCompiledShader())->Release();
			pShader->SetCompiledShader(nullptr);
		}
		
		// --------------------------------------------------------------------------------
		void DirectX11Renderer::CreateTexture( Texture *pTexture )
		{
/*			ID3D11ShaderResourceView *pTexView;
			const std::string path = pTexture->GetId().GetStrId();
			D3DX11_IMAGE_INFO ili;
			
			HR(D3DX11GetImageInfoFromFileA( path.c_str(), nullptr, &ili, nullptr));
			HR(D3DX11CreateShaderResourceViewFromFileA(m_pDevice, path.c_str(), nullptr, nullptr, &pTexView, nullptr));
			
			// store created texture in our container
			pTexture->SetData(pTexView);

			// fill texture properties
			pTexture->SetWidth(ili.Width);
			pTexture->SetHeight(ili.Height);

			switch(ili.Format)
			{
			case DXGI_FORMAT_R8G8B8A8_UNORM:
				pTexture->SetFormat(Texture::eTF_A8R8G8B8_UNORM);
				break;
			case DXGI_FORMAT_B8G8R8X8_UNORM:
				pTexture->SetFormat(Texture::eTF_X8R8G8B8_UNORM);// TODO bgr vs rgb here
				break;
			case DXGI_FORMAT_R8G8B8A8_UINT:
				pTexture->SetFormat(Texture::eTF_A8R8G8B8_UINT);
				break;
			default:
				pTexture->SetFormat(Texture::eTF_UNKNOWN);
			}
*/
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::ReleaseTexture( Texture *pTexture )
		{
			((ID3D11ShaderResourceView *)pTexture->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UseTexture ( Texture *pTexture )
		{	
			if(pTexture == nullptr)
				return;
			ID3D11ShaderResourceView *pSRV = (ID3D11ShaderResourceView*)pTexture->GetData();
			m_pDeviceContext->PSSetShaderResources(0, 1, &pSRV);

			// TODO this resource view needs to be released somehow
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex /* = 0 */)
		{
			SetMatrices();
			m_pDeviceContext->Draw(numPrimitives * m_numVerticesPerPrimitive, startVertex);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t /*numVertices*/, uint32_t startIndex /* = 0 */, uint32_t startVertex /* = 0 */)
		{
			SetMatrices();
			m_pDeviceContext->DrawIndexed(numPrimitives * m_numVerticesPerPrimitive, startIndex, startVertex);
		}


		// --------------------------------------------------------------------------------
		void DirectX11Renderer::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			D3D11_BUFFER_DESC desc;
			ID3D11Buffer *pVB = nullptr;
			desc.ByteWidth = pVertexBuffer->GetVertexCount() * pVertexBuffer->GetVertexSize();
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;//pVertexBuffer->GetVertexSize();
			desc.Usage = D3D11_USAGE_DYNAMIC;

			HR(m_pDevice->CreateBuffer(&desc, nullptr, &pVB));
			pVertexBuffer->SetData(pVB);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			// no offset??
			D3D11_MAPPED_SUBRESOURCE ms;
			m_pDeviceContext->Map((ID3D11Resource *)pVertexBuffer->GetData(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			*ppBuff = ms.pData;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			m_pDeviceContext->Unmap((ID3D11Resource *)pVertexBuffer->GetData(), NULL);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			((ID3D11Resource *)pVertexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			D3D11_BUFFER_DESC desc;
			ID3D11Buffer *pIB = nullptr;
			desc.ByteWidth = pIndexBuffer->GetIndexCount() * pIndexBuffer->GetIndexSize();
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;//pIndexBuffer->GetIndexSize();
			desc.Usage = D3D11_USAGE_DYNAMIC;

			m_pDevice->CreateBuffer(&desc, nullptr, &pIB);
			pIndexBuffer->SetData(pIB);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			// no offset?
			D3D11_MAPPED_SUBRESOURCE ms;
			m_pDeviceContext->Map((ID3D11Resource *)pIndexBuffer->GetData(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			*ppBuff = ms.pData;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			m_pDeviceContext->Unmap((ID3D11Resource *)pIndexBuffer->GetData(), 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			((ID3D11Resource *)pIndexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			m_pDebugTextRenderer->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{
			D3D11_INPUT_ELEMENT_DESC layout[12];
			numElems = 0;
			if(vertexFormat & (uint32_t)VertexBuffer::VertexFormat::xyz)
			{
				layout[numElems].SemanticName = "POSITION";
				layout[numElems].SemanticIndex = 0;
				layout[numElems].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				layout[numElems].InputSlot = 0;
				layout[numElems].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				layout[numElems].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[numElems].InstanceDataStepRate = 0;
				++numElems;
			}
			if(vertexFormat & (uint32_t)VertexBuffer::VertexFormat::normal)
			{
				layout[numElems].SemanticName = "NORMAL";
				layout[numElems].SemanticIndex = 0;
				layout[numElems].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				layout[numElems].InputSlot = 0;
				layout[numElems].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				layout[numElems].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[numElems].InstanceDataStepRate = 0;
				++numElems;
			}
			if(vertexFormat & (uint32_t)VertexBuffer::VertexFormat::diffuse)
			{
				layout[numElems].SemanticName = "COLOR";
				layout[numElems].SemanticIndex = 0;
				layout[numElems].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				layout[numElems].InputSlot = 0;
				layout[numElems].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				layout[numElems].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[numElems].InstanceDataStepRate = 0;
				++numElems;
			}
			if(vertexFormat & (uint32_t)VertexBuffer::VertexFormat::tex0)
			{
				layout[numElems].SemanticName = "TEXCOORD";
				layout[numElems].SemanticIndex = 0;
				layout[numElems].Format = DXGI_FORMAT_R32G32_FLOAT;
				layout[numElems].InputSlot = 0;
				layout[numElems].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				layout[numElems].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[numElems].InstanceDataStepRate = 0;
				++numElems;
			}

			pLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[numElems];
			memcpy(pLayoutDesc, layout, numElems * sizeof(D3D11_INPUT_ELEMENT_DESC));
		}


		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			ID3D11Buffer *pBuffer = (ID3D11Buffer *)pVertexBuffer->GetData();
			uint32_t stride = pVertexBuffer->GetVertexSize();
			uint32_t offset = 0;
			m_pDeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &stride, &offset);
			m_pCurrentVertexBuffer = pVertexBuffer;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			m_pCurrentIndexBuffer = pIndexBuffer;
			if(pIndexBuffer == nullptr || pIndexBuffer->GetData() == nullptr)
				return;
			ID3D11Buffer *pBuffer = (ID3D11Buffer *)pIndexBuffer->GetData();
			m_pDeviceContext->IASetIndexBuffer(pBuffer, DXGI_FORMAT_R32_UINT, 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			D3D11_PRIMITIVE_TOPOLOGY pt = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
			switch( primitiveTopology )
			{
			case ePT_PointList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
				m_numVerticesPerPrimitive = 1;
				break;
			case ePT_LineList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
				m_numVerticesPerPrimitive = 2;
				break;
			case ePT_LineStrip:
				pt = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
				m_numVerticesPerPrimitive = 2;
				break;
			case ePT_TriangleList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				m_numVerticesPerPrimitive = 3;
				break;
			case ePT_TriangleStrip:
				pt = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				m_numVerticesPerPrimitive = 3;
				break;
			default:
				break;
			}
			m_pDeviceContext->IASetPrimitiveTopology(pt);
			m_currentPrimitiveTopology = primitiveTopology;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::UseShader( Shader *pShader )
		{
//			if(!pShader || !pShader->IsReady())
//				return;
			if(pShader->GetType() == eST_VertexShader)
			{
				ID3D11VertexShader *pVertexShader = (ID3D11VertexShader *) pShader->GetCompiledShader();
				m_pDeviceContext->IASetInputLayout( (ID3D11InputLayout *)((DirectX11Shader*)pShader)->GetInputLayout() );
				m_pDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
			}
			else
			{
				ID3D11PixelShader *pPixelShader = (ID3D11PixelShader *) pShader->GetCompiledShader();
				m_pDeviceContext->PSSetShader(pPixelShader, nullptr, 0);
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EnableDepthBuffer()
		{
			m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilStateDepthEnabled, 1);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::DisableDepthBuffer()
		{
			m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilStateDepthDisabled, 1);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::SetRasterizerState( RasterizerStateIndex rsi )
		{
			m_pDeviceContext->RSSetState( m_pRasterizerStates[rsi] );
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EnableOrtographicProjection()
		{
			m_bPerspectiveProjection = false;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EnablePerspectiveProjection()
		{
			m_bPerspectiveProjection = true;
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EnableFillWireframe()
		{
			SetRasterizerState(eRSI_FillWireframe_CullBack_FrontCW);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Renderer::EnableFillSolid()
		{
			SetRasterizerState(eRSI_FillSolid_CullBack_FrontCW);
		}

		void DirectX11Renderer::SetMatrices()
		{
/*			struct MatrixBuffer
			{
				D3DXMATRIX mw, mv, mp;
			};
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			HR(m_pDeviceContext->Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
			MatrixBuffer *pMB = (MatrixBuffer *)mappedResource.pData;
			pMB->mw = (float *)*m_pWorldMatrix;
			pMB->mv = (float *)*m_pViewMatrix;
			pMB->mp = (m_bPerspectiveProjection ? (float *)*m_pPerspectiveProjectionMatrix : (float *)*m_pOrthographicProjectionMatrix);
			
			// transpose matrices before sending them to the shader. This is required by DX 11
			D3DXMatrixTranspose(&pMB->mw, &pMB->mw);
			D3DXMatrixTranspose(&pMB->mv, &pMB->mv);
			D3DXMatrixTranspose(&pMB->mp, &pMB->mp);

			m_pDeviceContext->Unmap(m_pMatrixBuffer, 0);
			m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pMatrixBuffer);
*/
		}

	}	// namespace Render
}	// namespace ro3d
