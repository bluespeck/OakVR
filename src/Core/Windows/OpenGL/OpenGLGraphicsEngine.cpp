
#include "../../Oak3DCoreConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

// include the OpenGL library file
#pragma comment (lib, "Opengl32.lib")

#include <cassert>

#include <windows.h>
#include <wingdi.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "OpenGLGraphicsEngine.h"
#include "../WindowsRenderWindow.h"
//#include "DirectX9DebugText.h"
//#include "DirectX9Shader.h"

#include "../../GraphicsEngineUtils.h"
#include "../../VertexBuffer.h"
#include "../../IndexBuffer.h"
#include "../../Texture.h"
#include "../../../Math/Matrix.h"
#include "../../../Math/Transform.h"


namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		OpenGLGraphicsEngine::OpenGLGraphicsEngine()
			: m_pDevice(nullptr)
			//, m_pDebugText(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Initialize()
		{
			HWND hWnd = reinterpret_cast<HWND>(m_pRenderWindow->GetOSHandle());
			HDC hdc = GetDC(hWnd);
			/////
			// create Direct3D device

			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 24; 
			pfd.cDepthBits = 32;  
			pfd.iLayerType = PFD_MAIN_PLANE;

			int  iPixelFormat; 

			// get the device context's best, available pixel format match  
			iPixelFormat = ChoosePixelFormat(hdc, &pfd); 

			// make that match the device context's current pixel format  
			SetPixelFormat(hdc, iPixelFormat, &pfd);

			m_pDevice = (HGLRC) wglCreateContext(hdc); 
			wglMakeCurrent (hdc, (HGLRC)m_pDevice);
			
			
			/////
			// create projection matrices
			m_pPerspectiveProjectionMatrix = new Math::Matrix();
			m_pOrthographicProjectionMatrix = new Math::Matrix();
			glMatrixMode(GL_PROJECTION);
			*m_pPerspectiveProjectionMatrix = Math::Transform::CreatePerspectiveProjectionTransform(3.141592f * 0.25f, 1.25f, 1.0f, 1000.0f);
			*m_pOrthographicProjectionMatrix = Math::Transform::CreateOthographicProjectionTransform(0.0f, (float)m_pRenderWindow->GetWidth(), 0.0f, (float)m_pRenderWindow->GetHeight(), 1.0f, 1000.0f);
			

			/////
			// initialize debug text
			//m_pDebugText = new DirectX9DebugText();
			//m_pDebugText->Init();

			InitializeStateObjects();
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::InitializeStateObjects()
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Render()
		{	
			// clear the window to a deep blue
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT); 
			
			/*
			m_pDevice->BeginScene();

			// render 3D stuff to back buffer

			m_pDebugText->OutputText(L"Testing 123...", 100, 100);

			m_pDevice->EndScene();
			*/
			
			SwapBuffers(wglGetCurrentDC());
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Cleanup()
		{
			//delete m_pDebugText;
			  
			wglMakeCurrent (NULL, NULL) ; 
			wglDeleteContext ((HGLRC)m_pDevice);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::Update(float dt)
		{

		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateShader(Shader *pShader)
		{
			/*
			DirectX9Shader *pSh = static_cast<DirectX9Shader *>(pShader);
			switch(pSh->GetType())
			{
			case eST_VertexShader:
				{
					LPD3DXBUFFER pShaderByteCode = nullptr;
					LPD3DXBUFFER pErrorMsg = nullptr;
					// compile vertex shader from file
					HR_ERR(D3DXCompileShaderFromFileW(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakVertexShader", "vs_2_0", 0, &pShaderByteCode, &pErrorMsg, nullptr), pErrorMsg);

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
					HR(D3DXCompileShaderFromFileW(pSh->GetId().GetStrId().c_str(), nullptr, nullptr, "OakPixelShader", "ps_2_0", 0, &pShaderByteCode, &pErrorMsg, nullptr));
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
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseShader(Shader *pShader)
		{
			/*
			if(pShader == nullptr)
				return;
			((IDirect3DResource9 *)pShader->GetCompiledShader())->Release();
			pShader->SetCompiledShader(nullptr);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateTexture( Texture *pTexture )
		{
			/*
			IDirect3DTexture9 *pTex;
			const std::wstring path = pTexture->GetId().GetStrId();
			D3DXIMAGE_INFO ili;

			HR(D3DXGetImageInfoFromFileW(path.c_str(), &ili));
			HR(D3DXCreateTextureFromFileW(m_pDevice, path.c_str(), &pTex));

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
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseTexture( Texture *pTexture )
		{
			/*
			((IDirect3DResource9 *)pTexture->GetData())->Release();
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			/*
			IDirect3DVertexBuffer9 *pVB = NULL;
			unsigned int length = pVertexBuffer->GetVertexCount() * pVertexBuffer->GetVertexSize();

			HR(m_pDevice->CreateVertexBuffer(length, D3DUSAGE_SOFTWAREPROCESSING, 0, D3DPOOL_DEFAULT, &pVB, nullptr));
			pVertexBuffer->SetData(pVB);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::LockVertexBuffer( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			/*
			// no offset??
			((IDirect3DVertexBuffer9 *)pVertexBuffer->GetData())->Lock(offsetToLock, sizeToLock, ppBuff, 0);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UnlockVertexBuffer( VertexBuffer *pVertexBuffer )
		{	
			/*
			((IDirect3DVertexBuffer9 *)pVertexBuffer)->Unlock();
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			/*
			((IDirect3DVertexBuffer9 *)pVertexBuffer->GetData())->Release();
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			/*
			IDirect3DIndexBuffer9 *pIB = NULL;
			
			m_pDevice->CreateIndexBuffer(pIndexBuffer->GetIndexCount() * pIndexBuffer->GetIndexSize(), D3DUSAGE_DYNAMIC, pIndexBuffer->GetIndexSize() == 2? D3DFMT_INDEX16: D3DFMT_INDEX32, D3DPOOL_DEFAULT, &pIB, nullptr);
			pIndexBuffer->SetData(pIB);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::LockIndexBuffer( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock, uint32_t sizeToLock, uint32_t flags )
		{	
			/*
			((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Lock(offsetToLock, sizeToLock, ppBuff, 0);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UnlockIndexBuffer( IndexBuffer *pIndexBuffer )
		{	
			//((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Unlock();
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::ReleaseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			//((IDirect3DIndexBuffer9 *)pIndexBuffer->GetData())->Release();
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::OutputText( const std::wstring &text, uint32_t x, uint32_t y)
		{
			//m_pDebugText->OutputText(text, x, y);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::CreateInputLayoutDesc(uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems)
		{
			/*
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
			*/
		}


		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseVertexBuffer( VertexBuffer *pVertexBuffer )
		{
			/*
			IDirect3DVertexBuffer9 *pBuffer = (IDirect3DVertexBuffer9 *)pVertexBuffer->GetData();
			uint32_t stride = pVertexBuffer->GetVertexSize();
			uint32_t offset = 0;
			m_pDevice->SetStreamSource(0, pBuffer, offset, stride);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseIndexBuffer( IndexBuffer *pIndexBuffer )
		{
			/*
			IDirect3DIndexBuffer9 *pBuffer = (IDirect3DIndexBuffer9 *)pIndexBuffer->GetData();
			m_pDevice->SetIndices(pBuffer);
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UsePrimitiveTopology( PrimitiveTopology primitiveTopology )
		{
			// Not available
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::UseShader( Shader *pShader )
		{
			/*
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
			*/
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::EnableDepthBuffer()
		{
			//m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		}

		// --------------------------------------------------------------------------------
		void OpenGLGraphicsEngine::DisableDepthBuffer()
		{
			//m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		}

	} // namespace Core
} // namespace Oak3D

#endif // OAK3D_RENDERER_OPENGL
