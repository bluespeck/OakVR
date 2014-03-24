#pragma once

#include "RendererUtils.h"
#include "Utils\Buffer.h"


#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <unordered_map>

namespace oakvr
{
	namespace math
	{
		class Matrix;
	}

	namespace core
	{
		class ResourceManager;
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
			~Renderer();

			bool Initialize();
			void Update( double dt );
			void Cleanup();

			void ClearBackground(const Color &color);
			void BeginDraw();
			void EndDraw();

			void RegisterMesh(std::shared_ptr<Mesh> pMesh);
			void RegisterTexture(const std::string &textureName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterVertexShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterPixelShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterGeometryShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterDomainShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			void RegisterHullShader(const std::string &shaderName, const std::shared_ptr<oakvr::core::MemoryBuffer> &buff);
			

			// render
			void DrawPrimitives(uint32_t numVertices, uint32_t startVertex = 0);
			void DrawIndexed(uint32_t numIndices, uint8_t indexStride = 4, uint32_t startIndex = 0, uint32_t startVertex = 0);

			// texture
			void CreateTexture	( Texture *texture );
			void ReleaseTexture	( Texture *texture );
			void UseTexture ( Texture *texture );
			
			void UseShader(std::shared_ptr<Shader> &pShader);
			void PrepareShaders();
			void SetVertexLayout(uint32_t vertexStride, const std::vector<VertexElementDescriptor> &vertexElementDescriptors);
			void BindAdditionalShaderParams();

			void SetRenderWindow( std::shared_ptr<RenderWindow> pRenderWindow );
			void SetResourceManager(std::shared_ptr<oakvr::core::ResourceManager> pRM);

			//void SetDebugTextRenderer( DebugTextRenderer *pDebugTextRenderer);
			//DebugTextRenderer * GetDebugTextRenderer() { return m_pDebugTextRenderer; }

			inline bool IsInitialized() { return m_bInitialized; }

			
		private:
			void InitCommon();
			

			std::shared_ptr<RenderWindow> m_pRenderWindow;
			std::shared_ptr<oakvr::core::ResourceManager> m_pResourceManager;

			class RendererImpl;
			std::unique_ptr<RendererImpl> m_pImpl;
			
			
			std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;

			typedef struct { std::shared_ptr<Shader> vs, ps, gs, ds, hs; }_Shaders;
			std::unordered_map<std::string, _Shaders> m_shaders;
			//DebugTextRenderer *m_pDebugTextRenderer;		// object used to draw debug text
			std::unique_ptr<MeshManager> m_pMeshManager;
			
			bool m_bInitialized;

		};
	}	// namespace render
}	// namespace oakvr
