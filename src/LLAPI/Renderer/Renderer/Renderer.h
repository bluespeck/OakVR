#pragma once

#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"
#include "Math/Matrix.h"
#include "Mesh.h"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <unordered_map>

namespace oakvr
{
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
		class Camera;
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

			void RegisterMesh(sp<Mesh> pMesh);
			auto GetRegisteredMesh(const StringId &name)->sp<Mesh>;
			void RegisterOneFrameMesh(sp<Mesh> pMesh);
			void UnregisterMesh(sp<Mesh> pMesh);
			void RegisterTexture(const StringId &textureName, sp<oakvr::core::MemoryBuffer> pBuff);
			
			void RegisterShaderProgram(const StringId &shaderProgramName);
			
			// render
			void DrawPrimitives(uint32_t numVertices, uint32_t startVertex = 0);
			void DrawIndexed(uint32_t numIndices, uint8_t indexStride = 4, uint32_t startIndex = 0, uint32_t startVertex = 0);

			// texture
			void CreateTexture	( Texture *texture );
			void ReleaseTexture	( Texture *texture );
			void UseTexture ( Texture *texture );
			
			void UseShaderProgram(sp<ShaderProgram> pShader);
			void SetVertexLayout(uint32_t vertexStride, const std::vector<VertexElementDescriptor> &vertexElementDescriptors);
			
			void SetRenderWindow( sp<RenderWindow> pRenderWindow );
			void SetResourceManager(sp<oakvr::core::ResourceManager> pRM);

			void SetCurrentCamera(const sp<Camera> &pCamera) { m_pCurrentCamera = pCamera; }
			void SetViewMatrix(const oakvr::math::Matrix &mat) { m_viewMatrix = mat; }
			void SetProjMatrix(const oakvr::math::Matrix &mat) { m_projMatrix = mat; }
			auto GetViewMatrix() const -> const oakvr::math::Matrix& { return m_viewMatrix; }

			void OnResize(unsigned int newWidth, unsigned int newHeight);

			bool IsValid();	//true if the native render context/device are valid
#define DECLARE_ENABLEDISABLE_FCT(fName) \
	void Enable ## fName();\
	void Disable ## fName();\
	void Toggle ## fName();\
	bool Is ## fName ## Enabled() const { return m_b ## fName ## Enabled; }

			DECLARE_ENABLEDISABLE_FCT(Wireframe);
			DECLARE_ENABLEDISABLE_FCT(Culling);
			DECLARE_ENABLEDISABLE_FCT(DepthTest);
			DECLARE_ENABLEDISABLE_FCT(Blending);
#undef DECLARE_ENABLEDISABLE_FCT

		private:
			void InitCommon();

			void RenderMeshes(const std::vector<sp<Mesh>> &meshes);
			void RenderMeshElems(const Mesh::MeshElementVector &meshElems);
			void UpdateShaderParams(sp<ShaderProgram> pShader);

			sp<RenderWindow> m_pRenderWindow;
			sp<oakvr::core::ResourceManager> m_pResourceManager;

			class RendererImpl;
			std::unique_ptr<RendererImpl> m_pImpl;
			
			std::unordered_map<StringId, sp<Texture>> m_textures;

			std::unordered_map<StringId, sp<ShaderProgram>> m_shaderPrograms;
			
			std::unique_ptr<MeshManager> m_pMeshManager;

			sp<Camera> m_pCurrentCamera;

			oakvr::math::Matrix m_viewMatrix;
			oakvr::math::Matrix m_projMatrix;
			oakvr::math::Matrix m_worldMatrix;

#define DECLARE_ENABLEDISABLE_VAR(fName, defaultValue) bool m_b ## fName ## Enabled = defaultValue;
			DECLARE_ENABLEDISABLE_VAR(Wireframe, false);
			DECLARE_ENABLEDISABLE_VAR(Culling, true);
			DECLARE_ENABLEDISABLE_VAR(DepthTest, true);
			DECLARE_ENABLEDISABLE_VAR(Blending, true);
#undef DECLARE_ENABLEDISABLE_VAR
		};
	}	// namespace render
}	// namespace oakvr


