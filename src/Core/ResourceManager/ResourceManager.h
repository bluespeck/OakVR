#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>

#include <memory>
#include <unordered_map>
#include <vector>

#include "ResourceManager/IResource.h"
#include "ResourceManager/EmptyResource.h"
#include "Utils/StringId.h"
#include "Utils/Singleton.h"
#include "Utils/Buffer.h"

namespace oakvr
{
	namespace core
	{
		class ResourceManager: public oakvr::Singleton<ResourceManager>
		{
		public:
			void Initialize();

			std::shared_ptr<MemoryBuffer> GetResource(const std::string &id);
			
			void ReleaseResource(const std::string &id);

			ResourceManager();
			~ResourceManager();
		
			void AddPathsFromFolder(const std::string &path);
			
		private:
			mutable std::mutex m_rmThreadsShouldStopMutex;
			mutable std::condition_variable m_rmThreadsShouldStopCondVar;
			mutable bool m_bRMThreadsShouldStop;
			
			std::vector<std::string> m_toBeLoaded;
			std::vector<std::string> m_toBeUnloaded;	// to be released
			std::unordered_map<std::string, std::shared_ptr<MemoryBuffer>> m_mapResources;
			std::unordered_map<std::string, std::string> m_mapPaths;
			mutable std::mutex m_inMemoryMutex;

			mutable std::mutex m_toBeLoadedMutex;
			mutable std::condition_variable m_toBeLoadedCondVar;

			mutable std::mutex m_unloadMutex;
			mutable std::condition_variable m_unloadCondVar;


			std::unique_ptr<std::thread> m_pRMLoadThread;
			std::unique_ptr<std::thread> m_pRMUnloadThread;
		};

	}
}
