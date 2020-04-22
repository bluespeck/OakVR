#pragma once

#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"
#include "Math/Matrix44.h"
#include "Mesh.h"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <mutex>

namespace oakvr::core
{
	class ResourceManager;
}

namespace oakvr::render
{
	class RenderWindow;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class ShaderProgram;
	struct Color;
	class DebugTextRenderer;
	class MeshManager;
	class Renderable;
	class RenderableManager;
	class Camera;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		auto Initialize() -> bool;
		auto Update(double dt) -> void;
		auto Cleanup() -> void;

		auto ClearBackground(const Color& color) -> void;
		auto BeginDraw() -> void;
		auto EndDraw() -> void;

		auto RegisterMesh(sp<Mesh> pMesh) -> void;
		auto GetRegisteredMesh(const StringId& name)->sp<Mesh>;
		auto RegisterOneFrameMesh(sp<Mesh> pMesh) -> void;
		auto UnregisterMesh(sp<Mesh> pMesh) -> void;
		auto RegisterTexture(const StringId& textureName, sp<oakvr::core::MemoryBuffer> pBuff) -> void;

		auto RegisterShaderProgram(const StringId& shaderProgramName) -> void;

		auto RegisterRenderable(sp<Mesh> pMesh, oakvr::math::Matrix44 transform) -> void;
		auto UnregisterAllRenderables() -> void;

		// render
		auto DrawPrimitives(uint32_t numVertices, uint32_t startVertex = 0) -> void;
		auto DrawIndexed(uint32_t numIndices, uint8_t indexStride = 4, uint32_t startIndex = 0, uint32_t startVertex = 0) -> void;

		// texture
		auto CreateTexture(Texture* texture) -> void;
		auto ReleaseTexture(Texture* texture) -> void;
		auto UseTexture(Texture* texture) -> void;

		auto UseShaderProgram(sp<ShaderProgram> pShader) -> void;
		auto SetVertexLayout(uint32_t vertexStride, const std::vector<VertexElementDescriptor>& vertexElementDescriptors) -> void;

		auto SetRenderWindow(sp<RenderWindow> pRenderWindow) -> void;
		auto SetResourceManager(sp<oakvr::core::ResourceManager> pRM) -> void;

		auto SetCurrentCamera(const sp<Camera>& pCamera) -> void { m_pCurrentCamera = pCamera; }
		auto SetViewMatrix(const oakvr::math::Matrix44& mat) -> void { m_viewMatrix = mat; }
		auto SetProjMatrix(const oakvr::math::Matrix44& mat) -> void { m_projMatrix = mat; }
		auto GetViewMatrix() const -> const oakvr::math::Matrix44& { return m_viewMatrix; }

		auto OnResize(unsigned int newWidth, unsigned int newHeight) -> void;

		auto IsValid() -> bool;	//true if the native render context/device are valid
#define DECLARE_ENABLEDISABLE_FCT(fName) \
auto Enable ## fName() -> void;\
auto Disable ## fName() -> void;\
auto Toggle ## fName() -> void;\
auto Is ## fName ## Enabled() const -> bool { return m_b ## fName ## Enabled; }

		DECLARE_ENABLEDISABLE_FCT(Wireframe);
		DECLARE_ENABLEDISABLE_FCT(Culling);
		DECLARE_ENABLEDISABLE_FCT(DepthTest);
		DECLARE_ENABLEDISABLE_FCT(Blending);
#undef DECLARE_ENABLEDISABLE_FCT

	private:
		auto InitCommon() -> void;

		auto RenderMeshes(const std::vector<sp<Mesh>>& meshes) -> void;
		auto RenderMeshElems(const Mesh::MeshElementVector& meshElems) -> void;
		auto RenderRenderables(const std::vector<sp<Renderable>>& renderables) -> void;
		auto UpdateShaderParams(sp<ShaderProgram> pShader) -> void;

	private:
		sp<RenderWindow> m_pRenderWindow;
		sp<oakvr::core::ResourceManager> m_pResourceManager;

		class RendererImpl;
		std::unique_ptr<RendererImpl> m_pImpl;

		std::unordered_map<StringId, sp<Texture>> m_textures;

		std::unordered_map<StringId, sp<ShaderProgram>> m_shaderPrograms;

		std::unique_ptr<MeshManager> m_pMeshManager;
		std::unique_ptr<RenderableManager> m_pRenderableManager;

		sp<Camera> m_pCurrentCamera;

		oakvr::math::Matrix44 m_viewMatrix;
		oakvr::math::Matrix44 m_projMatrix;
		oakvr::math::Matrix44 m_worldMatrix;

#define DECLARE_ENABLEDISABLE_VAR(fName, defaultValue) bool m_b ## fName ## Enabled = defaultValue;
		DECLARE_ENABLEDISABLE_VAR(Wireframe, false);
		DECLARE_ENABLEDISABLE_VAR(Culling, true);
		DECLARE_ENABLEDISABLE_VAR(DepthTest, true);
		DECLARE_ENABLEDISABLE_VAR(Blending, true);
#undef DECLARE_ENABLEDISABLE_VAR

		std::mutex m_cleanupMutex;
	};
}


