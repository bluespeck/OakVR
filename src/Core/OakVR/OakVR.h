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
	public:

		auto RegisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void;
		auto UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void;

		///////////////////////////////////////////////////////////////////////////////////
		// resources related interface
		auto RegisterSubFolderPaths(const std::string &path) -> bool;
		auto GetResource(const std::string &id) -> sp<oakvr::core::MemoryBuffer>;
				
		auto Cleanup() -> void;
		auto RegisterUserInitializer(std::function<void()> fct) -> void { 
																			m_userInitializers.push_back(fct); }
		auto RegisterEngineInitializer(std::function<void()> fct) -> void { 
																			m_engineInitializers.push_back(fct); }


	private:
		auto Initialize() -> bool;
		auto Update() -> bool;

		auto Update(TimeDeltaType dt) -> bool;

		auto TriggerInputEvents() -> void;
		auto DrawInterface() -> void;
		auto DrawMeshes() -> void;
		auto DrawDebugText() -> void;
		
		auto DrawMeshBoundingBoxes() -> void;

		// window related
		friend auto WindowSizeChangedCallback(void *pNativeHandler, int w, int h) -> void;
		friend auto WindowFocusChangedCallback(void *pNativeHandler, int focused) -> void;
		friend auto WindowPositionChangedCallback(void *pNativeHandler, int x, int y) -> void;

		friend class Singleton < OakVR >;
		friend auto oakvrUpdate() -> bool;
		friend auto oakvrInit(std::vector<std::string> cmdLine) -> bool;
		friend auto oakvrExit() -> void;


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
