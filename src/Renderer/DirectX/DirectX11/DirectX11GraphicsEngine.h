
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX11GRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_DIRECTX11GRAPHICSENGINE_H__

#include "Renderer/IRenderer/GraphicsEngine.h"


struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;

namespace Oak3D
{
	namespace Render
	{
		class DirectX11DebugText;
		class Shader;
		struct Color;

		class DirectX11GraphicsEngine : public GraphicsEngine
		{
		public:

			enum RasterizerStateIndex
			{
				eRSI_First = 0,
				eRSI_FillSolid_CullBack_FrontCCW = eRSI_First,
				eRSI_FillSolid_CullBack_FrontCW,
				eRSI_FillSolid_CullFront_FrontCCW,
				eRSI_FillSolid_CullFront_FrontCW,
				eRSI_FillWireframe_CullBack_FrontCCW,
				eRSI_FillWireframe_CullBack_FrontCW,
				eRSI_FillWireframe_CullFront_FrontCCW,
				eRSI_FillWireframe_CullFront_FrontCW,
				eRSI_Last = eRSI_FillWireframe_CullFront_FrontCW,
				eRSI_Count
			};

			// constructors
			DirectX11GraphicsEngine();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Cleanup();

			virtual void ClearBackground(const Color &color);
			virtual void SwapBuffers();
			virtual void BeginDraw();
			virtual void EndDraw();

			virtual void DrawPrimitives(uint32_t numPrimitives);
			virtual void DrawIndexedPrimitives(uint32_t numPrimitives);


			virtual void CreateTexture	( Texture *texture );
			virtual void ReleaseTexture	( Texture *texture );
			virtual void UseTexture ( Texture *texture );
			
			virtual void CreateVertexBuffer	( VertexBuffer *pVertexBuffer );
			virtual void LockVertexBuffer	( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			virtual void UnlockVertexBuffer	( VertexBuffer *pVertexBuffer );
			virtual void ReleaseVertexBuffer( VertexBuffer *pVertexBuffer );
			virtual void UseVertexBuffer( VertexBuffer *pVertexBuffer );
			
			virtual void CreateIndexBuffer	( IndexBuffer *ibuff );
			virtual void LockIndexBuffer	( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			virtual void UnlockIndexBuffer	( IndexBuffer *pIndexBuffer );
			virtual void ReleaseIndexBuffer	( IndexBuffer *pIndexBuffer );
			virtual void UseIndexBuffer( IndexBuffer *pIndexBuffer );

			virtual void UsePrimitiveTopology( PrimitiveTopology primitiveTopology );

			virtual void CreateShader( Shader *pShader );
			virtual void ReleaseShader( Shader *pShader );
			virtual void UseShader( Shader *pShader );			

			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y);

			// misc
			void CreateInputLayoutDesc( uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems );
			void InitializeStateObjects();

			void EnableDepthBuffer();
			void DisableDepthBuffer();

			void SetRasterizerState( RasterizerStateIndex rsi );


			ID3D11Device *GetDevice() { return m_pDevice; }
			ID3D11DeviceContext *GetDeviceContext() { return m_pDeviceContext; }

		private:
			IDXGISwapChain *m_pSwapChain;             // the swap chain interface
			ID3D11Device *m_pDevice;                     // Direct3D device interface
			ID3D11DeviceContext *m_pDeviceContext;           // Direct3D device context

			ID3D11RenderTargetView *m_pBackBufferRenderTargetView;

			DirectX11DebugText *m_pDebugText;		// object used to draw debug text

			// directx state objects
			ID3D11DepthStencilState *m_pDepthStencilStateDepthDisabled;
			ID3D11DepthStencilState *m_pDepthStencilStateDepthEnabled;
			ID3D11RasterizerState *m_pRasterizerStates[eRSI_Count];

			VertexBuffer *m_pCurrentVertexBuffer;
			IndexBuffer *m_pCurrentIndexBuffer;
			Shader *m_pCurrentVertexShader;
			Shader *m_pCurrentPixelShader;
		};
	}	// namespace Render
}	// namespace Oak3D

#endif
