#pragma once

#include "Utils/Singleton.h"
#include "Interface.h"
#include "Time/Timer.h"
#include "Renderer/Renderer/Mesh.h"
#include "OakVR/Camera.h"
#include "Updatable.h"

#include "OakVR/UtilityTypes.h"

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

		void RegisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable);
		void UnregisterUpdatable(std::shared_ptr<oakvr::Updatable> pUpdatable);

		auto CreateMesh(const std::string &name, std::shared_ptr<oakvr::core::MemoryBuffer> pMeshBuffer, std::shared_ptr<oakvr::render::Material> pMaterial) -> std::shared_ptr < oakvr::render::Mesh > ;
		void RegisterMesh(std::shared_ptr<oakvr::render::Mesh> pMesh);
		auto GetRegisteredMesh(const std::string &name) -> std::shared_ptr<oakvr::render::Mesh>;
		void UnregisterMesh(std::shared_ptr<oakvr::render::Mesh> pMesh);
		void TransformMesh(const std::string &meshName, const oakvr::math::Matrix &mat);

		void RegisterShader(std::string shaderName);

		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color);
		void DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &color, const oakvr::render::Color &startColor);

		void RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		auto GetCamera(const std::string &cameraId) -> std::shared_ptr<oakvr::render::Camera>;
		auto GetCurrentCamera()->std::shared_ptr<oakvr::render::Camera>;
		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const std::string &cameraId);

		void SetRenderWindowSize(unsigned int width, unsigned int height);
		void SetRenderWindowPosition(int x, int y);
		void SetRenderWindowTitle(const std::string &title);

		bool HasFocus();

		///////////////////////////////////////////////////////////////////////////////////
		// resources related interface
		void RegisterSubFolderPaths(const std::string &path);
		auto GetResource(const std::string &id) -> std::shared_ptr<oakvr::core::MemoryBuffer>;
				
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

		void OnWindowSizeChanged(void *pNativeHandler, int width, int height);		
		void OnWindowFocusChanged(void *pNativeHandler, int focused);

	private:
		OakVR();
		~OakVR();

	private:
		Timer m_timer;

		std::shared_ptr<oakvr::core::ResourceManager> m_pRM;
		std::shared_ptr<oakvr::render::RenderWindow> m_pRW;
		std::shared_ptr<oakvr::render::Renderer> m_pRenderer;
		std::shared_ptr<oakvr::render::CameraManager> m_pCM;
		
		std::vector<std::shared_ptr<oakvr::Updatable>> m_pUpdatables;

		std::vector<std::function<void()>> m_initializers;
	};
}	// namespace oakvr

#define _OAKVR_REGISTER_INITIALIZER(myInitializer, file, line) \
	struct OakVRInitializer  ## file ## line\
	{\
		OakVRInitializer  ## file ## line() { oakvr::OakVR::GetInstance().RegisterInitializer(myInitializer); }\
	} oakVRInitializer ## __FILE__ ## line;

// OAKVR initializer; Use it in a compilation unit to have one of your functions called
#define OAKVR_REGISTER_INITIALIZER(myInitializer) _OAKVR_REGISTER_INITIALIZER(myInitializer, __FILE__, __LINE__)
