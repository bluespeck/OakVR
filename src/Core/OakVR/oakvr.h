#pragma once

#include "OakVR/Engine.h"
#include "Utils/Singleton.h"
#include "Interface.h"
#include "Updateable.h"

#include <functional>
#include <vector>
#include <memory>

namespace oakvr
{
	namespace render
	{
		class Mesh;
		class Camera;
	}
	class OakVR : public Singleton<OakVR>
	{
		friend class Singleton < OakVR > ;
		friend bool oakvrUpdate();
		friend bool oakvrInit(std::vector<std::string> cmdLine);
		friend void oakvrExit();
	public:
		void CleanupEngine();
		void RegisterInitializer(std::function<void()> fct) { m_initializers.push_back(fct); }

		void RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);
		void UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable);

		void RegisterMesh(std::shared_ptr<oakvr::render::Mesh> pMesh);
		void RegisterShader(std::string shaderName);

		void RegisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void UnregisterCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		std::shared_ptr<oakvr::render::Camera> GetCamera(const std::string &cameraId);
		std::shared_ptr<oakvr::render::Camera> GetCurrentCamera();
		void SetCurrentCamera(std::shared_ptr<oakvr::render::Camera> pCamera);
		void SetCurrentCamera(const std::string &cameraId);

		void RegisterSubFolderPaths(const std::string &path);
		std::shared_ptr<oakvr::core::MemoryBuffer> GetResource(const std::string &id);

	private:
		OakVR();
		~OakVR();
		
		bool Update();

	private:
		Engine m_engine;

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