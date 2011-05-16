
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__

//#if defined(OAK3D_WINDOWS) && defined(OAK3D_DIRECTX_11)

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "../GraphicsEngine.h"
#include "DirectXUtils.h"


namespace Oak3D
{
	namespace Core
	{
		class DirectX11DebugText;
		class Shader;

		class DirectX11GraphicsEngine : public GraphicsEngine
		{
		public:
			// constructors
			DirectX11GraphicsEngine();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Render();
			virtual void Cleanup();

			virtual void CreateShader( Shader *pShader );
			virtual void ReleaseShader( Shader *pShader );
			
			virtual void CreateTexture	( Texture *texture );
			virtual void ReleaseTexture	( Texture *texture );
			
			virtual void CreateVertexBuffer	( VertexBuffer *pVertexBuffer );
			virtual void LockVertexBuffer	( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			virtual void UnlockVertexBuffer	( VertexBuffer *pVertexBuffer );
			virtual void ReleaseVertexBuffer( VertexBuffer *pVertexBuffer );
			
			virtual void CreateIndexBuffer	( IndexBuffer *ibuff );
			virtual void LockIndexBuffer	( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			virtual void UnlockIndexBuffer	( IndexBuffer *pIndexBuffer );
			virtual void ReleaseIndexBuffer	( IndexBuffer *pIndexBuffer );

			virtual void OutputText( const std::wstring &text, uint32_t x, uint32_t y);

			void CreateInputLayoutDesc( uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems );
			void Render( VertexBuffer *pVertexBuffer, Shader *pShader );

		private:
			IDXGISwapChain *m_pSwapChain;             // the swap chain interface
			ID3D11Device *m_pDevice;                     // Direct3D device interface
			ID3D11DeviceContext *m_pDeviceContext;           // Direct3D device context

			ID3D11RenderTargetView *m_pBackBufferRenderTargetView;

			DirectX11DebugText *m_pDebugText;		// object used to draw debug text

		};
	}
}

#endif

//#endif
