#pragma once

#include "Renderer/IRenderer/IRenderer.h"
#include "Renderer/IRenderer/Shader.h"
#include "Renderer/IRenderer/DebugTextRenderer.h"

struct IDirect3DDevice9;
struct IDirect3DSurface9;

namespace ro3d
{
	namespace Render
	{
		class DirectX9Renderer : public IRenderer
		{
		public:

			// constructors
			DirectX9Renderer();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Cleanup();

			virtual void ClearBackground(const Color &color);
			virtual void SwapBuffers();
			virtual void BeginDraw();
			virtual void EndDraw();

			virtual void DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex = 0);
			virtual void DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t numVertices = 0, uint32_t startIndex = 0, uint32_t startVertex = 0);

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
			virtual ro3d::Math::Matrix CreateViewMatrix(ro3d::Math::Vector3 eye, ro3d::Math::Vector3 lookAt, ro3d::Math::Vector3 up);

			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y);

			virtual void EnableOrtographicProjection();
			virtual void EnablePerspectiveProjection();
			virtual void EnableFillWireframe();
			virtual void EnableFillSolid();

			
			// misc
			void CreateInputLayoutDesc( uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems );
			void InitializeStateObjects();

			void EnableDepthBuffer();
			void DisableDepthBuffer();

			IDirect3DDevice9 *GetDevice() { return m_pDevice; }

		private:
			IDirect3DDevice9 *m_pDevice;                     // Direct3D device interface
			IDirect3DSurface9 *m_pRenderTarget;
		};
	}	// namespace Render
}	// namespace ro3d

