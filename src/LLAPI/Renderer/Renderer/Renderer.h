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
		class ShaderProgram;
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
			void RegisterOneFrameMesh(std::shared_ptr<Mesh> pMesh);
			void RegisterTexture(const std::string &textureName, std::shared_ptr<oakvr::core::MemoryBuffer> pBuff);
			
			void RegisterShaderProgram(const std::string &shaderProgramName);
			
			// render
			void DrawPrimitives(uint32_t numVertices, uint32_t startVertex = 0);
			void DrawIndexed(uint32_t numIndices, uint8_t indexStride = 4, uint32_t startIndex = 0, uint32_t startVertex = 0);

			// texture
			void CreateTexture	( Texture *texture );
			void ReleaseTexture	( Texture *texture );
			void UseTexture ( Texture *texture );
			
			void UseShaderProgram(std::shared_ptr<ShaderProgram> pShader);
			void SetVertexLayout(uint32_t vertexStride, const std::vector<VertexElementDescriptor> &vertexElementDescriptors);
			
			void SetRenderWindow( std::shared_ptr<RenderWindow> pRenderWindow );
			void SetResourceManager(std::shared_ptr<oakvr::core::ResourceManager> pRM);

			inline bool IsInitialized() { return m_bInitialized; }

		private:
			void InitCommon();

			void RenderMeshes(const std::vector<std::shared_ptr<Mesh>> &meshes);
			void UpdateShaderParams(std::shared_ptr<ShaderProgram> pShader);

			std::shared_ptr<RenderWindow> m_pRenderWindow;
			std::shared_ptr<oakvr::core::ResourceManager> m_pResourceManager;

			class RendererImpl;
			std::unique_ptr<RendererImpl> m_pImpl;
			
			
			std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;

			std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaderPrograms;
			//DebugTextRenderer *m_pDebugTextRenderer;		// object used to draw debug text
			std::unique_ptr<MeshManager> m_pMeshManager;
			
			bool m_bInitialized;

		};
	}	// namespace render
}	// namespace oakvr
