#pragma once

#include "OakVR/UtilityTypes.h"
#include "Utils/Types.h"
#include "OakVR/UtilityTypes.h"

#include "Utils/Buffer.h"

#include "Utils/StringId.h"

namespace oakvr
{
	// forward declarations
	namespace render
	{
		class Renderer;
		class RenderWindow;
		class CameraManager;
		class Mesh;
		class Material;
		struct Color;
		class Camera;

	}

	namespace math
	{
		class Vector3;
		class Matrix;
	}

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

		auto CreateMesh(const StringId &name, sp<oakvr::core::MemoryBuffer> pMeshBuffer, sp<oakvr::render::Material> pMaterial)->sp < oakvr::render::Mesh >;
		void RegisterMesh(sp<oakvr::render::Mesh> pMesh);
		auto GetRegisteredMesh(const StringId &name)->sp<oakvr::render::Mesh>;
		void UnregisterMesh(sp<oakvr::render::Mesh> pMesh);
		void TransformMesh(const StringId &meshName, const oakvr::math::Matrix &mat);

		void RegisterShader(StringId shaderName);

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color);
		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor);

		void RegisterCamera(sp<oakvr::render::Camera> pCamera);
		void UnregisterCamera(sp<oakvr::render::Camera> pCamera);
		auto GetCamera(const StringId &cameraId)->sp<oakvr::render::Camera>;
		auto GetCurrentCamera()->sp<oakvr::render::Camera>;
		void SetCurrentCamera(sp<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const StringId &cameraId);

		void SetRenderWindowSize(unsigned int width, unsigned int height);
		void SetRenderWindowPosition(int x, int y);
		void SetRenderWindowTitle(const std::string &title);

		bool HasFocus();

		void OnWindowSizeChanged(void *pNativeHandler, int width, int height);
		void OnWindowFocusChanged(void *pNativeHandler, int focused);
		void OnWindowPositionChanged(void *pNativeHandler, int x, int y);

#define DECLARE_ENABLEDISABLE_FCT(fName) \
	void Enable ## fName();\
	void Disable ## fName();\
	void Toggle ## fName();\
	bool Is ## fName ## Enabled() const;

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