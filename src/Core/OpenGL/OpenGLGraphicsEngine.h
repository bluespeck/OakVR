
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__

//#if defined(OAK3D_OPENGL)

#include <gl.h>
#include <glu.h>
#include <glut.h>

#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "opengl32.lib")

namespace Oak3D
{
	namespace Core
	{		
		class OpenGLGraphicsEngine : public GraphicsEngine
		{
		public:

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
		};
	}	// namespace Core
}	// namespace Oak3D
