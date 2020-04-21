#pragma once

#include "OakVR/UtilityTypes.h"
#include "Utils/Types.h"
#include "OakVR/UtilityTypes.h"

#include "Utils/Buffer.h"

#include "Utils/StringId.h"

#define DECLARE_ENABLEDISABLE_FCT(fName) \
	auto Enable ## fName() -> void;\
	auto Disable ## fName() -> void;\
	auto Toggle ## fName() -> void;\
	auto Is ## fName ## Enabled() const -> bool;

// forward declarations
namespace oakvr::render
{
	
	class Renderer;
	class RenderWindow;
	class CameraManager;
	class Mesh;
	class Material;
	struct Color;
	class Camera;
}

namespace oakvr::math
{
	class Vector3;
	class Matrix;
}

namespace oakvr
{
	///////////////////////////////////////////////////////////////////////////////////
	// render related interface
	class OakVRRenderUnit
	{
	public:
		auto GetScreenSize() const->ScreenSize;
		auto GetRenderWindowSize() const->WindowSize;
		auto GetRenderWindowWidth() const -> float;
		auto GetRenderWindowHeight() const -> float;
		auto GetRenderWindowPositionX() const -> float;
		auto GetRenderWindowPositionY() const -> float;

		auto CreateMesh(const StringId &name, sp<oakvr::core::MemoryBuffer> pMeshBuffer, sp<oakvr::render::Material> pMaterial) -> sp < oakvr::render::Mesh >;
		auto RegisterMesh(sp<oakvr::render::Mesh> pMesh) -> void;
		auto GetRegisteredMesh(const StringId &name) -> sp < oakvr::render::Mesh >;
		auto UnregisterMesh(sp<oakvr::render::Mesh> pMesh) -> void;
		auto TransformMesh(const StringId &meshName, const oakvr::math::Matrix &mat) -> void;

		auto RegisterShader(StringId shaderName) -> void;

		auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color) -> void;
		auto DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor) -> void;

		auto RegisterCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto UnregisterCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto GetCamera(const StringId &cameraId) -> sp<oakvr::render::Camera>;
		auto GetCurrentCamera() -> sp<oakvr::render::Camera>;
		auto SetCurrentCamera(sp<oakvr::render::Camera> pCamera) -> void;
		auto SetCurrentCamera(const StringId &cameraId) -> void;

		auto SetRenderWindowSize(unsigned int width, unsigned int height) -> void;
		auto SetRenderWindowPosition(int x, int y) -> void;
		auto SetRenderWindowTitle(const std::string &title) -> void;

		auto HasFocus() -> bool;

		auto OnWindowSizeChanged(void *pNativeHandler, int width, int height) -> void;
		auto OnWindowFocusChanged(void *pNativeHandler, int focused) -> void;
		auto OnWindowPositionChanged(void *pNativeHandler, int x, int y) -> void;

		DECLARE_ENABLEDISABLE_FCT(Wireframe)
		DECLARE_ENABLEDISABLE_FCT(Culling)
		DECLARE_ENABLEDISABLE_FCT(DepthTest)
		DECLARE_ENABLEDISABLE_FCT(Blending)
#undef DECLARE_ENABLEDISABLE_FCT

	protected:
		OakVRRenderUnit();
	protected:
		sp<oakvr::render::RenderWindow> m_pRW;
		sp<oakvr::render::Renderer> m_pRenderer;
		sp<oakvr::render::CameraManager> m_pCM;
	};
}