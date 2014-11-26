#pragma once

#include "Utils/Singleton.h"
#include "Interface.h"
#include "Time/Timer.h"
#include "Renderer/Renderer/Mesh.h"
#include "OakVR/Camera.h"
#include "Updatable.h"

#include "OakVR/UtilityTypes.h"
#include "Utils/Types.h"

#include <memory>

namespace oakvr
{
	// forward declarations
	namespace render
	{
		class Renderer;
		class RenderWindow;
		class CameraManager;
	}
	namespace core
	{
		class ResourceManager;
	}

	// Engine class
	class OakVR : public Singleton<OakVR>
	{
		friend class Singleton < OakVR >;
		friend bool oakvrUpdate();
		friend bool oakvrInit(std::vector<std::string> cmdLine);
		friend void oakvrExit();
	public:

		///////////////////////////////////////////////////////////////////////////////////
		// render related interface
		auto GetScreenSize() const -> ScreenSize;
		auto GetRenderWindowSize() const -> WindowSize;
		auto GetRenderWindowWidth() const -> float;
		auto GetRenderWindowHeight() const -> float;
		auto GetRenderWindowPositionX() const -> float;
		auto GetRenderWindowPositionY() const -> float;

		void RegisterUpdatable(sp<oakvr::Updatable> pUpdatable);
		void UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable);

		auto CreateMesh(const std::string &name, sp<oakvr::core::MemoryBuffer> pMeshBuffer, sp<oakvr::render::Material> pMaterial) -> sp < oakvr::render::Mesh > ;
		void RegisterMesh(sp<oakvr::render::Mesh> pMesh);
		auto GetRegisteredMesh(const std::string &name) -> sp<oakvr::render::Mesh>;
		void UnregisterMesh(sp<oakvr::render::Mesh> pMesh);
		void TransformMesh(const std::string &meshName, const oakvr::math::Matrix &mat);

		void RegisterShader(std::string shaderName);

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color);
		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor);

		void RegisterCamera(sp<oakvr::render::Camera> pCamera);
		void UnregisterCamera(sp<oakvr::render::Camera> pCamera);
		auto GetCamera(const std::string &cameraId) -> sp<oakvr::render::Camera>;
		auto GetCurrentCamera()->sp<oakvr::render::Camera>;
		void SetCurrentCamera(sp<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const std::string &cameraId);

		void SetRenderWindowSize(unsigned int width, unsigned int height);
		void SetRenderWindowPosition(int x, int y);
		void SetRenderWindowTitle(const std::string &title);

		bool HasFocus();

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

		///////////////////////////////////////////////////////////////////////////////////
		// resources related interface
		auto RegisterSubFolderPaths(const std::string &path)->bool;
		auto GetResource(const std::string &id) -> sp<oakvr::core::MemoryBuffer>;
				
		void Cleanup();
		void RegisterInitializer(std::function<void()> fct) { m_initializers.push_back(fct); }
		
	private:
		bool Initialize();
		bool Update();

		bool Update(float dt);

		void TriggerInputEvents();
		void DrawInterface();
		void DrawMeshes();
		void DrawDebugText();
		
		void DrawMeshBoundingBoxes();

		// window related
		friend void WindowSizeChangedCallback(void *pNativeHandler, int w, int h);
		friend void WindowFocusChangedCallback(void *pNativeHandler, int focused);
		friend void WindowPositionChangedCallback(void *pNativeHandler, int x, int y);

		void OnWindowSizeChanged(void *pNativeHandler, int width, int height);		
		void OnWindowFocusChanged(void *pNativeHandler, int focused);
		void OnWindowPositionChanged(void *pNativeHandler, int x, int y);

	private:
		OakVR();
		~OakVR();

	private:
		Timer m_timer;

		sp<oakvr::core::ResourceManager> m_pRM;
		sp<oakvr::render::RenderWindow> m_pRW;
		sp<oakvr::render::Renderer> m_pRenderer;
		sp<oakvr::render::CameraManager> m_pCM;
		
		std::vector<sp<oakvr::Updatable>> m_pUpdatables;

		std::vector<std::function<void()>> m_initializers;
	};
}	// namespace oakvr

#define _OAKVR_REGISTER_UPDATABLE_INITIALIZER(myInitializer, file, line) \
	struct OakVRInitializer  ## file ## line\
	{\
		OakVRInitializer  ## file ## line() { oakvr::OakVR::GetInstance().RegisterInitializer(myInitializer); }\
	} oakVRInitializer ## __FILE__ ## line;

// creates a global object that upon construction initializes an object of the <className> class
#define OAKVR_REGISTER_UPDATABLE(className) _OAKVR_REGISTER_UPDATABLE_INITIALIZER([](){::oakvr::RegisterUpdatable(std::make_shared<className>());}, __FILE__, __LINE__)
