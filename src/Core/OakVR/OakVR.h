#pragma once

#include "Utils/Singleton.h"
#include "Time/Timer.h"

#include "OakVR/Camera.h"
#include "OakVR/Updatable.h"

#include "OakVR/UtilityTypes.h"

#include "Utils/Types.h"


#include "OakVR/OakVRObjectUnit.h"
#include "OakVR/OakVRRenderUnit.h"

namespace oakvr
{
	using TimeDeltaType = float;

	// forward declarations
	namespace core
	{
		class ResourceManager;
	}

	// Engine class
	class OakVR : public Singleton<OakVR>, public OakVRRenderUnit, public OakVRObjectUnit
	{
		friend class Singleton < OakVR >;
		friend bool oakvrUpdate();
		friend bool oakvrInit(std::vector<std::string> cmdLine);
		friend void oakvrExit();
	public:

		void RegisterUpdatable(sp<oakvr::Updatable> pUpdatable);
		void UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable);

		///////////////////////////////////////////////////////////////////////////////////
		// resources related interface
		auto RegisterSubFolderPaths(const std::string &path)->bool;
		auto GetResource(const std::string &id) -> sp<oakvr::core::MemoryBuffer>;
				
		void Cleanup();
		void RegisterUserInitializer(std::function<void()> fct) { 
			m_userInitializers.push_back(fct); }
		void RegisterEngineInitializer(std::function<void()> fct) { 
			m_engineInitializers.push_back(fct); }


	private:
		bool Initialize();
		bool Update();

		bool Update(TimeDeltaType dt);

		void TriggerInputEvents();
		void DrawInterface();
		void DrawMeshes();
		void DrawDebugText();
		
		void DrawMeshBoundingBoxes();

		// window related
		friend void WindowSizeChangedCallback(void *pNativeHandler, int w, int h);
		friend void WindowFocusChangedCallback(void *pNativeHandler, int focused);
		friend void WindowPositionChangedCallback(void *pNativeHandler, int x, int y);



	private:
		OakVR();
		~OakVR();

	private:
		Timer m_timer;

		sp<oakvr::core::ResourceManager> m_pRM;
		
		
		std::vector<sp<oakvr::Updatable>> m_pUpdatables;

		std::vector<std::function<void()>> m_userInitializers;
		std::vector<std::function<void()>> m_engineInitializers;
	};
}	// namespace oakvr

#define _OAKVR_REGISTER_UPDATABLE_INITIALIZER(myInitializer, counter) \
	struct OakVRInitializer  ## counter\
	{\
		OakVRInitializer  ## counter() { oakvr::OakVR::GetInstance().RegisterUserInitializer(myInitializer); }\
	} oakVRInitializer ## counter;

// creates a global object that upon construction initializes an object of the <className> class
#define OAKVR_REGISTER_UPDATABLE(className) _OAKVR_REGISTER_UPDATABLE_INITIALIZER([](){::oakvr::RegisterUpdatable(std::make_shared<className>());}, __COUNTER__)

// creates a global object that upon construction 
#define _OAKVR_REGISTER_ENGINE_INITIALIZER(myInitializer, tag) \
	struct OakVREngineInitializer  ## tag\
	{\
		OakVREngineInitializer  ## tag() { oakvr::OakVR::GetInstance().RegisterEngineInitializer(myInitializer); }\
	} oakVREngineInitializer ## tag;
