#pragma once

#include "Utils/RenderUtils.h"
#include "Renderer/Renderer/Material.h"
#include "OakVR/Camera.h"
#include "Renderer/Renderer/Mesh.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include "Updatable.h"

#include "Utils/Buffer.h"
#include "Utils/Types.h"

#include <memory>
#include <vector>

#define DECLARE_ENABLEDISABLE_FCT(fName)\
		auto Enable ## fName() -> void;	\
		auto Disable ## fName() -> void;\
		auto Toggle ## fName() -> void;	\
		auto Is ## fName ## Enabled() -> bool;


namespace oakvr::render
{
	typedef std::vector<oakvr::render::VertexElementDescriptor> VertexDescriptor;
				
	auto CreateMesh(const StringId &name, const oakvr::render::VertexDescriptor &vertexDescriptor, 
			const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer,	
			sp<Material> pMaterial, std::vector<StringId> textureNames // for each texcoord
			) -> MeshSharedPointer;
	auto CreateMesh(const StringId &name, const StringId &resourceId, sp<oakvr::render::Material> pMaterial) -> MeshSharedPointer;
	auto RemoveMesh(const StringId &name) -> void;
	auto GetMesh(const StringId &name) -> MeshSharedPointer;
	auto TransformMesh(const StringId &name, const oakvr::math::Matrix44 &mat) -> void;

	auto RegisterShader(const StringId &shaderName) -> void;

	auto RegisterCamera(CameraSharedPointer pCamera) -> void;
	auto UnregisterCamera(CameraSharedPointer pCamera) -> void;
	auto GetCamera(const StringId &cameraId) -> CameraSharedPointer;
	auto GetCurrentCamera() -> CameraSharedPointer;
	auto SetCurrentCamera(CameraSharedPointer pCamera) -> void;
	auto SetCurrentCamera(const StringId &cameraId) -> void;

	auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color) -> void;
	auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor) -> void;

	auto SetRenderWindowPosition(int x, int y) -> void;
	auto SetRenderWindowSize(unsigned int width, unsigned int height) -> void;
	auto GetRenderWindowPositionX() -> int;
	auto GetRenderWindowPositionY() -> int;
	auto GetRenderWindowWidth() -> float;
	auto GetRenderWindowHeight() -> float;
	auto SetRenderWindowTitle(const std::string &title) -> void;
	auto RenderWindowHasFocus() -> bool;

	auto ScreenCoordsToWindowClient(oakvr::math::Vector2)->oakvr::math::Vector2;

	DECLARE_ENABLEDISABLE_FCT(Wireframe)
	DECLARE_ENABLEDISABLE_FCT(Culling)
	DECLARE_ENABLEDISABLE_FCT(DepthTest)
	DECLARE_ENABLEDISABLE_FCT(Blending)
#undef DECLARE_ENABLEDISABLE_FCT
		
} // namespace oakvr::render

namespace oakvr
{
	auto RegisterUpdatable(UpdateableSharedPointer pUpdatable) -> void;
	auto UnregisterUpdatable(UpdateableSharedPointer pUpdatable) -> void;

	namespace core
	{
		auto RegisterSubFolderPaths(const std::string &path) -> bool;
		auto GetResource(const StringId &id) -> sp<oakvr::core::MemoryBuffer>;
	}
} // namespace oakvr