
// --------------------------------------------------------------------------------
// Written by		Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OPENGLGRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_OPENGLGRAPHICSENGINE_H__

#include <map>

#include "Renderer/IRenderer/GraphicsEngine.h"

namespace Oak3D
{
	namespace Render
	{
		class OpenGLDebugText;
		class VertexBuffer;
		class IndexBuffer;

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

			void *GetDevice() { return m_pDevice; }

		private:
			void *m_pDevice;                    // OpenGL device interface (context)
			void *m_pWorkerThreadDevice;		// worker thread context
			long m_mainThreadId;
			OpenGLDebugText *m_pDebugText;		// object used to draw debug text
			long m_shaderProgramId;

			VertexBuffer *m_pCurrentVertexBuffer;
			IndexBuffer *m_pCurrentIndexBuffer;
		};
	}	// namespace Render
}	// namespace Oak3D

#endif

