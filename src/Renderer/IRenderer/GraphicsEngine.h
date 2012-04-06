
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDER_GRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_RENDER_GRAPHICSENGINE_H__

#include <cstdint>
#include <string>
#include "GraphicsEngineUtils.h"

#include "Core/Math/Vector3.h"



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
		struct Color;
		class DebugTextRenderer;

		class GraphicsEngine
		{
		public:
			GraphicsEngine();
			virtual ~GraphicsEngine();

			virtual void Initialize(){}
			virtual void Update( float dt ){}
			virtual void Cleanup() {}

			virtual void ClearBackground(const Color &color) = 0;
			virtual void SwapBuffers() = 0;
			virtual void BeginDraw() {};
			virtual void EndDraw() {};

			// render
			virtual void DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex = 0) = 0;
			virtual void DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t numVertices, uint32_t startIndex = 0, uint32_t startVertex = 0) = 0;

			// texture
			virtual void CreateTexture	( Texture *texture ) = 0;
			virtual void ReleaseTexture	( Texture *texture ) = 0;
			virtual void UseTexture ( Texture *texture ) = 0;
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
			virtual Oak3D::Math::Matrix CreateViewMatrix(Oak3D::Math::Vector3 eye, Oak3D::Math::Vector3 lookAt, Oak3D::Math::Vector3 up) = 0; 

			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y);

			virtual void EnableOrtographicProjection() = 0;
			virtual void EnablePerspectiveProjection() = 0;
			virtual void EnableFillWireframe() = 0;
			virtual void EnableFillSolid() = 0;

			void SetRenderWindow( RenderWindow *pRenderWindow );
			void SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer);
			DebugTextRenderer * GetDebugTextRenderer() { return m_pDebugTextRenderer; }

			inline Math::Matrix *GetWorldMatrix();
			inline Math::Matrix *GetViewMatrix();
			inline Math::Matrix *GetOrthographicProjectionMatrix();
			inline Math::Matrix *GetPerspectiveProjectionMatrix();

			inline bool IsInitialized() { return m_bInitialized; }

		protected:
			RenderWindow *m_pRenderWindow;
			Math::Matrix *m_pWorldMatrix, *m_pViewMatrix, *m_pPerspectiveProjectionMatrix, *m_pOrthographicProjectionMatrix;

			PrimitiveTopology m_currentPrimitiveTopology;
			uint8_t m_numVerticesPerPrimitive;

			VertexBuffer *m_pCurrentVertexBuffer;
			IndexBuffer *m_pCurrentIndexBuffer;
			Shader *m_pCurrentVertexShader;
			Shader *m_pCurrentPixelShader;

			DebugTextRenderer *m_pDebugTextRenderer;		// object used to draw debug text

			bool m_bInitialized;
		};
		
		// --------------------------------------------------------------------------------		
		Math::Matrix *GraphicsEngine::GetWorldMatrix()
		{
			return m_pWorldMatrix;
		}

		// --------------------------------------------------------------------------------		
		Math::Matrix *GraphicsEngine::GetViewMatrix()
		{
			return m_pViewMatrix;
		}

		// --------------------------------------------------------------------------------		
		Math::Matrix *GraphicsEngine::GetPerspectiveProjectionMatrix()
		{
			return m_pPerspectiveProjectionMatrix;
		}

		// --------------------------------------------------------------------------------		
		Math::Matrix *GraphicsEngine::GetOrthographicProjectionMatrix()
		{
			return m_pOrthographicProjectionMatrix;
		}

	}	// namespace Render
}	// namespace Oak3D

#endif
