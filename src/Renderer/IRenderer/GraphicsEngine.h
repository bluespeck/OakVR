
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_GRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_GRAPHICSENGINE_H__

#include <cstdint>
#include <string>
#include "GraphicsEngineUtils.h"


namespace Oak3D
{
	namespace Math
	{
		class Matrix;
	}
	namespace Render
	{
		class RenderWindow;
		class Texture;
		class VertexBuffer;
		class IndexBuffer;
		class Shader;

		class GraphicsEngine
		{
		public:
			GraphicsEngine();
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
			virtual void UseVertexBuffer( VertexBuffer *pVertexBuffer ) = 0;
			// index buffer
			virtual void CreateIndexBuffer	( IndexBuffer *ibuff ) = 0;
			virtual void LockIndexBuffer	( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 ) = 0;
			virtual void UnlockIndexBuffer	( IndexBuffer *pIndexBuffer ) = 0;
			virtual void ReleaseIndexBuffer	( IndexBuffer *pIndexBuffer ) = 0;
			virtual void UseIndexBuffer( IndexBuffer *pIndexBuffer ) = 0;
			virtual void UsePrimitiveTopology( PrimitiveTopology primitiveTopology ) = 0;
			// shader
			virtual void CreateShader( Shader *pShader ) = 0;
			virtual void ReleaseShader( Shader *pShader ) = 0;
			virtual void UseShader( Shader *pShader ) = 0;

			// misc
			virtual void OutputText( const std::wstring &text, uint32_t x, uint32_t y);

			void SetRenderWindow( RenderWindow *pRenderWindow );

			inline Math::Matrix *GetViewMatrix();
			inline Math::Matrix *GetOrthographicProjectionMatrix();
			inline Math::Matrix *GetPerspectiveProjectionMatrix();

		protected:
			RenderWindow *m_pRenderWindow;
			Math::Matrix *m_pViewMatrix, *m_pPerspectiveProjectionMatrix, *m_pOrthographicProjectionMatrix;
		};
		
		// --------------------------------------------------------------------------------		
		inline Math::Matrix *GraphicsEngine::GetViewMatrix()
		{
			return m_pViewMatrix;
		}

		// --------------------------------------------------------------------------------		
		inline Math::Matrix *GraphicsEngine::GetPerspectiveProjectionMatrix()
		{
			return m_pPerspectiveProjectionMatrix;
		}

		// --------------------------------------------------------------------------------		
		inline Math::Matrix *GraphicsEngine::GetOrthographicProjectionMatrix()
		{
			return m_pOrthographicProjectionMatrix;
		}
	}	// namespace Render
}	// namespace Oak3D

#endif
