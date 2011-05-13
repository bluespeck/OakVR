
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_GRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_GRAPHICSENGINE_H__

#include <cstdint>
#include <string>
#include "GraphicsEngineUtils.h"


namespace Oak3D
{
	namespace Core
	{
		class RenderWindow;
		class Texture;
		class VertexBuffer;
		class IndexBuffer;

		class GraphicsEngine
		{
		public:
			GraphicsEngine():m_pRenderWindow(nullptr){}
			virtual ~GraphicsEngine();

			

			virtual void Initialize(){}
			virtual void Update( float dt ){}
			virtual void Render(void){}
			virtual void Cleanup() {}

			// texture
			virtual void CreateTexture	( Texture *texture ) = 0;
			virtual void ReleaseTexture	( Texture *texture ) = 0;
			// vertex buffer
			virtual void CreateVertexBuffer	( VertexBuffer *pVertexBuffer ) = 0;
			virtual void LockVertexBuffer	( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 ) = 0;
			virtual void UnlockVertexBuffer	( VertexBuffer *pVertexBuffer ) = 0;
			virtual void ReleaseVertexBuffer( VertexBuffer *pVertexBuffer ) = 0;
			// index buffer
			virtual void CreateIndexBuffer	( IndexBuffer *ibuff ) = 0;
			virtual void LockIndexBuffer	( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 ) = 0;
			virtual void UnlockIndexBuffer	( IndexBuffer *pIndexBuffer ) = 0;
			virtual void ReleaseIndexBuffer	( IndexBuffer *pIndexBuffer ) = 0;
			// shader
			virtual void *CreateShaderFromFile( const std::wstring &fileName, ShaderType eShaderType ) = 0;
			virtual void ReleaseShader( void *pShader, ShaderType eShaderType ) = 0;

			void SetRenderWindow( RenderWindow *pRenderWindow );

		protected:
			RenderWindow *m_pRenderWindow;
		};
	}
}

#endif
