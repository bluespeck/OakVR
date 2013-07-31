#pragma once

#include <map>

#include "Renderer/IRenderer/IRenderer.h"


namespace oakvr
{
	namespace Render
	{
		class OpenGLRenderer : public IRenderer
		{
		public:

			// constructors
			OpenGLRenderer();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Cleanup();

			virtual void ClearBackground(const Color &color);
			virtual void SwapBuffers();
			virtual void BeginDraw();
			virtual void EndDraw();

			virtual void DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex = 0);
			virtual void DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t numVertices, uint32_t startIndex = 0, uint32_t startVertex = 0);

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

			virtual void EnableDepthBuffer();
			virtual void DisableDepthBuffer();

			virtual oakvr::Math::Matrix CreateViewMatrix(oakvr::Math::Vector3 eye, oakvr::Math::Vector3 lookAt, oakvr::Math::Vector3 up);

			virtual void EnableOrtographicProjection();
			virtual void EnablePerspectiveProjection();
			virtual void EnableFillWireframe();
			virtual void EnableFillSolid();

		private:
			// misc
			void CreateInputLayoutDesc( uint32_t vertexFormat, void *&pLayoutDesc, uint32_t &numElems );
			void InitializeStateObjects();
			void UseShaderProgram();
			void SetMatrices();

			
			void *GetDevice() { return m_pDevice; }

		private:
			void *m_pDevice;                    // OpenGL device interface (context)
			void *m_pWorkerThreadDevice;		// worker thread context
			long m_mainThreadId;
			long m_shaderProgramId;

			VertexBuffer *m_pCurrentVertexBuffer;
			IndexBuffer *m_pCurrentIndexBuffer;

			bool m_bPerspectiveProjection;
		};
	}	// namespace Render
}	// namespace oakvr

