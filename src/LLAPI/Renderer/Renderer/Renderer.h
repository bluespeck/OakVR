#pragma once

#include "RendererUtils.h"

#include <cstdint>
#include <string>
#include <memory>

namespace oakvr
{
	namespace Math
	{
		class Matrix;
	}
	namespace render
	{
		class RenderWindow;
		class Texture;
		class VertexBuffer;
		class IndexBuffer;
		class Shader;
		struct Color;
		class DebugTextRenderer;

		class Renderer
		{
		public:
			Renderer();
			Renderer(Renderer&&) = default;
			~Renderer();

			void Initialize();
			void Update( float dt );
			void Cleanup();

			void ClearBackground(const Color &color);
			void SwapBuffers();
			void BeginDraw();
			void EndDraw();

			// render
			void DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex = 0);
			void DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t numVertices, uint32_t startIndex = 0, uint32_t startVertex = 0);

			// texture
			void CreateTexture	( Texture *texture );
			void ReleaseTexture	( Texture *texture );
			void UseTexture ( Texture *texture );
			// vertex buffer
			void CreateVertexBuffer	( VertexBuffer *pVertexBuffer );
			void LockVertexBuffer	( VertexBuffer *pVertexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void UnlockVertexBuffer	( VertexBuffer *pVertexBuffer );
			void ReleaseVertexBuffer( VertexBuffer *pVertexBuffer );
			void UseVertexBuffer( VertexBuffer *pVertexBuffer );
			// index buffer
			void CreateIndexBuffer	( IndexBuffer *ibuff );
			void LockIndexBuffer	( IndexBuffer *pIndexBuffer, void **ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0 );
			void UnlockIndexBuffer	( IndexBuffer *pIndexBuffer );
			void ReleaseIndexBuffer	( IndexBuffer *pIndexBuffer );
			void UseIndexBuffer( IndexBuffer *pIndexBuffer );
			void UsePrimitiveTopology( PrimitiveTopology primitiveTopology );

			// shader
			void CreateShader( Shader *pShader );
			void ReleaseShader( Shader *pShader );
			void UseShader( Shader *pShader );

			//void SetRenderWindow( RenderWindow *pRenderWindow );
			//void SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer);
			//DebugTextRenderer * GetDebugTextRenderer() { return m_pDebugTextRenderer; }

			inline bool IsInitialized() { return m_bInitialized; }

		private:
			std::shared_ptr<RenderWindow> m_pRenderWindow;
			class RendererImpl;
			std::unique_ptr<RendererImpl> m_pImpl;

			//VertexBuffer *m_pCurrentVertexBuffer;
			//IndexBuffer *m_pCurrentIndexBuffer;
			//Shader *m_pCurrentVertexShader;
			//Shader *m_pCurrentPixelShader;

			//DebugTextRenderer *m_pDebugTextRenderer;		// object used to draw debug text

			bool m_bInitialized;

		};
		
	}	// namespace Render
}	// namespace oakvr
