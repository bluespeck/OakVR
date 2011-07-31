
// --------------------------------------------------------------------------------
// Written by		Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OPENGLGRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_OPENGLGRAPHICSENGINE_H__



#include "../../GraphicsEngine.h"

namespace Oak3D
{
	namespace Core
	{		
		class OpenGLGraphicsEngine : public GraphicsEngine
		{
		public:

			// constructors
			OpenGLGraphicsEngine();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Render();
			virtual void Cleanup();

			virtual void CreateTexture	( Texture *texture );
			virtual void ReleaseTexture	( Texture *texture );

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

			virtual void OutputText( const std::wstring &text, uint32_t x, uint32_t y);

			// misc
			void CreateInputLayoutDesc( uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems );
			void InitializeStateObjects();

			void EnableDepthBuffer();
			void DisableDepthBuffer();

			void *GetDevice() { return m_pDevice; }

		private:
			void *m_pDevice;                     // OpenGL device interface
			//IDirect3DSurface9 *m_pRenderTarget;
			//DirectX9DebugText *m_pDebugText;		// object used to draw debug text
		};
	}	// namespace Core
}	// namespace Oak3D

#endif

