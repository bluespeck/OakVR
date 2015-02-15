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


namespace oakvr
{
	namespace render
	{
		typedef std::vector<oakvr::render::VertexElementDescriptor> VertexDescriptor;
				
		auto CreateMesh(const StringId &name, const oakvr::render::VertexDescriptor &vertexDescriptor, 
			const oakvr::core::MemoryBuffer &vertexBuffer, uint8_t indexStride, const oakvr::core::MemoryBuffer &indexBuffer,	
			sp<Material> pMaterial, std::vector<StringId> textureNames // for each texcoord
			)->sp<oakvr::render::Mesh>;
		auto CreateMesh(const StringId &name, const StringId &resourceId, sp<oakvr::render::Material> pMaterial)->sp<oakvr::render::Mesh>;
		auto RemoveMesh(const StringId &name) -> void;
		auto GetMesh(const StringId &name)->sp<oakvr::render::Mesh>;
		auto TransformMesh(const StringId &name, const oakvr::math::Matrix &mat) -> void;

		auto RegisterShader(const StringId &shaderName) -> void;

		auto RegisterCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto UnregisterCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto GetCamera(const StringId &cameraId)->sp<oakvr::render::Camera>;
		auto GetCurrentCamera()->sp<oakvr::render::Camera>;
		auto SetCurrentCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto SetCurrentCamera(const StringId &cameraId) -> void;

		auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color) -> void;
		auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor) -> void;

		auto SetRenderWindowPosition(int x, int y) -> void;
		auto SetRenderWindowSize(unsigned int width, unsigned int height) -> void;
		auto GetRenderWindowPositionX()->int;
		auto GetRenderWindowPositionY()->int;
		auto GetRenderWindowWidth()->float;
		auto GetRenderWindowHeight()->float;
		auto SetRenderWindowTitle(const std::string &title) -> void;
		auto RenderWindowHasFocus()->bool;

		auto ScreenCoordsToWindowClient(oakvr::math::Vector2)->oakvr::math::Vector2;

#define DECLARE_ENABLEDISABLE_FCT(fName) \
		void Enable ## fName();\
		void Disable ## fName();\
		void Toggle ## fName();\
		bool Is ## fName ## Enabled();

		DECLARE_ENABLEDISABLE_FCT(Wireframe)
		DECLARE_ENABLEDISABLE_FCT(Culling)
		DECLARE_ENABLEDISABLE_FCT(DepthTest)
		DECLARE_ENABLEDISABLE_FCT(Blending)
#undef DECLARE_ENABLEDISABLE_FCT
		
	}

	auto RegisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void;
	auto UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void;

	namespace core
	{
		auto RegisterSubFolderPaths(const std::string &path)->bool;
		auto GetResource(const StringId &id)->sp<oakvr::core::MemoryBuffer>;
	}
} // namespace oakvr