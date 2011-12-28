
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

// include the Direct3D Library files
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <windows.h>
#include <windowsx.h>
#include <d3dx11.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <D3D11Shader.h>
#include <vector>

#include <cassert>

#include "Oak3D/Engine.h"

#include "Renderer/DirectX/DirectXUtils.h"
#include "DirectX11GraphicsEngine.h"
#include "DirectX11DebugText.h"
#include "DirectX11Shader.h"

#include "Renderer/IRenderer/WindowsRenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngineUtils.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Texture.h"
#include "Core/Math/Matrix.h"

#include "Core/Time/Timer.h"



namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX11GraphicsEngine::DirectX11GraphicsEngine()
		: m_pDevice(nullptr)
		, m_pSwapChain(nullptr)
		, m_pDeviceContext(nullptr)
		, m_pDebugText(nullptr)
		, m_pDepthStencilStateDepthEnabled(nullptr)
		, m_pDepthStencilStateDepthDisabled(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Initialize()
		{
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			SetWindowTextW(hWnd, L"Oak3D [DX11]");
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
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | D3D11_CREATE_DEVICE_DEBUG;		// allow windowed/fullscreen switch
			D3D_FEATURE_LEVEL featLevel[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1
			};

			HR(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 
				0, featLevel, 6, D3D11_SDK_VERSION, &scd, &m_pSwapChain,	&m_pDevice,	nullptr, &m_pDeviceContext));
			
			/////
			// set the render target

			// get the address of the back buffer
			ID3D11Texture2D *pBackBufferTexture;
			m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferTexture);

			// use the back buffer address to create the render target

			HR(m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pBackBufferRenderTargetView));
			pBackBufferTexture->Release();

			// set the render target as the back buffer
			m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBufferRenderTargetView, NULL);


			/////
			// set the viewport

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (float)m_pRenderWindow->GetWidth();
			viewport.Height = (float)m_pRenderWindow->GetHeight();
			viewport.MinDepth = 0;
			viewport.MaxDepth = 1.0;

			m_pDeviceContext->RSSetViewports(1, &viewport);

			/////
			// create projection matrices
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			D3DXMatrixPerspectiveFovLH((D3DXMATRIX *)(void *)m_pPerspectiveProjectionMatrix, 3.141592f * 0.25f, 1.25f, 1, 1000);
			D3DXMatrixOrthoLH((D3DXMATRIX *)(void *)m_pOrthographicProjectionMatrix, viewport.Width, viewport.Height, 0, 1000);

			/////
			// initialize debug text
			m_pDebugText = new DirectX11DebugText();
			m_pDebugText->Init();

			
			
			InitializeStateObjects();
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::InitializeStateObjects()
		{
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
		void DirectX11GraphicsEngine::Render()
		{			
			m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRenderTargetView, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

			// render 3D stuff to back buffer 

			char str[128];
			sprintf_s(str, "FPS: %.0f", (1.0f / Oak3D::Engine::GetTimer()->GetDeltaTime()));
			m_pDebugText->OutputText(str, 10, 10);

			HR(m_pSwapChain->Present(0, 0));
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::Cleanup()
		{
			delete m_pDebugText;

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
		HRESULT CreateInputLayoutDescFromVertexShaderSignature( ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout )
		{
			// Reflect shader info
			ID3D11ShaderReflection* pVertexShaderReflection = NULL;	
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
			for ( uint32_t i=0; i< shaderDesc.InputParameters; i++ )
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
		void DirectX11GraphicsEngine::CreateShader(Shader *pShader)
		{
			DirectX11Shader *pSh = static_cast<DirectX11Shader *>(pShader);
			switch(pSh->GetType())
			{
			case eST_VertexShader:
				{
					ID3D10Blob *pShaderByteCode = nullptr;
					ID3D10Blob *pErrorMsg = nullptr;
					// compile vertex shader from file
					HR_ERR(D3DX11CompileFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr), pErrorMsg);
					
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
					HR(D3DX11CompileFromFileA(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakPixelShader", "ps_4_0", 0, 0, nullptr, &pShaderByteCode, &pErrorMsg, nullptr));
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
		void DirectX11GraphicsEngine::ReleaseShader(Shader *pShader)
		{
			if(pShader == nullptr)
				return;
			((ID3D11Resource *)pShader->GetCompiledShader())->Release();
			pShader->SetCompiledShader(nullptr);
		}
		
		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateTexture( Texture *pTexture )
		{
			ID3D11Resource *pTex;
			const std::string path = pTexture->GetId().GetStrId();
			D3DX11_IMAGE_INFO ili;
			
			HR(D3DX11GetImageInfoFromFileA( path.c_str(), nullptr, &ili, nullptr));
			HR(D3DX11CreateTextureFromFileA(m_pDevice, path.c_str(), nullptr, nullptr, &pTex, nullptr));
			
			// store created texture in our container
			pTexture->SetData(pTex);

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

			HR(m_pDevice->CreateBuffer(&desc, NULL, &pVB));
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

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::OutputText( const std::string &text, uint32_t x, uint32_t y)
		{
			m_pDebugText->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{
			D3D11_INPUT_ELEMENT_DESC layout[12];
			numElems = 0;
			if(vertexFormat & VertexBuffer::eVF_XYZ)
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
			if(vertexFormat & VertexBuffer::eVF_Normal)
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
			if(vertexFormat & VertexBuffer::eVF_Diffuse)
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
			if(vertexFormat & VertexBuffer::eVF_Tex0)
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
		void DirectX11GraphicsEngine::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			ID3D11Buffer *pBuffer = (ID3D11Buffer *)pVertexBuffer->GetData();
			uint32_t stride = pVertexBuffer->GetVertexSize();
			uint32_t offset = 0;
			m_pDeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &stride, &offset);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			ID3D11Buffer *pBuffer = (ID3D11Buffer *)pIndexBuffer->GetData();
			m_pDeviceContext->IASetIndexBuffer(pBuffer, DXGI_FORMAT_R32_UINT, 0);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			D3D11_PRIMITIVE_TOPOLOGY pt = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
			switch( primitiveTopology )
			{
			case ePT_PointList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case ePT_LineList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case ePT_LineStrip:
				pt = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
				break;
			case ePT_TriangleList:
				pt = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			case ePT_TriangleStrip:
				pt = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				break;
			default:
				break;
			}
			m_pDeviceContext->IASetPrimitiveTopology(pt);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::UseShader( Shader *pShader )
		{
			
			if(pShader->GetType() == eST_VertexShader)
			{
				ID3D11VertexShader *pVertexShader = (ID3D11VertexShader *) pShader->GetCompiledShader();
				m_pDeviceContext->IASetInputLayout( ((DirectX11Shader*)pShader)->GetInputLayout() );
				m_pDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
			}
			else
			{
				ID3D11PixelShader *pPixelShader = (ID3D11PixelShader *) pShader->GetCompiledShader();
				m_pDeviceContext->PSSetShader(pPixelShader, nullptr, 0);
			}
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::EnableDepthBuffer()
		{
			m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilStateDepthEnabled, 1);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::DisableDepthBuffer()
		{
			m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilStateDepthDisabled, 1);
		}

		// --------------------------------------------------------------------------------
		void DirectX11GraphicsEngine::SetRasterizerState( RasterizerStateIndex rsi )
		{
			m_pDeviceContext->RSSetState( m_pRasterizerStates[rsi] );
		}

	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_11
