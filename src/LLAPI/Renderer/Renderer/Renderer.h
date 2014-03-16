#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "Utils\Buffer.h"

namespace oakvr
{
	namespace math
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
		class MeshManager;
		class Mesh;

		class Renderer
		{
		public:
			Renderer();
			//Renderer(Renderer&&) = default;
			~Renderer();

			bool Initialize();
			void Update( double dt );
			void Cleanup();

			void ClearBackground(const Color &color);
			void BeginDraw();
			void EndDraw();

			void RegisterMesh(std::shared_ptr<Mesh> pMesh);
			void RegisterVertexShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterPixelShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);

			// render
			void DrawPrimitives(uint32_t numPrimitives, uint32_t startVertex = 0);
			void DrawIndexedPrimitives(uint32_t numPrimitives, uint32_t startIndex = 0, uint32_t startVertex = 0);

			// texture
			void CreateTexture	( Texture *texture );
			void ReleaseTexture	( Texture *texture );
			void UseTexture ( Texture *texture );
			void UseShader(std::shared_ptr<Shader> &pShader);
			void PrepareShaders();

			void SetRenderWindow( std::shared_ptr<RenderWindow> &pRenderWindow );
			//void SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer);
			//DebugTextRenderer * GetDebugTextRenderer() { return m_pDebugTextRenderer; }

			inline bool IsInitialized() { return m_bInitialized; }

		private:
			void InitCommon();

			std::shared_ptr<RenderWindow> m_pRenderWindow;
			class RendererImpl;
			std::unique_ptr<RendererImpl> m_pImpl;
			
			
			std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
			std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
			//DebugTextRenderer *m_pDebugTextRenderer;		// object used to draw debug text
			std::unique_ptr<MeshManager> m_pMeshManager;
			bool m_bInitialized;

		};
	}	// namespace render
}	// namespace oakvr
