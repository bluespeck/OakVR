#pragma once

#include <vector>
#include <algorithm>

#include <mutex>
#include <thread>
#include <memory>
#include <condition_variable>

#include "ResourceManager/IResource.h"
#include "ResourceManager/EmptyResource.h"
#include "Utils/StringId.h"
#include "Utils/Singleton.h"

namespace oakvr
{
	namespace Core
	{
		class ResourceManager: public oakvr::Singleton<ResourceManager>
		{
		public:
			void Initialize();

			std::shared_ptr<IResource> GetResource(const StringId &id);
			
			void ReleaseResource(std::shared_ptr<IResource> pRes);
			void ReleaseResource(const StringId &id);

			ResourceManager();
			~ResourceManager();
			
		private:
			static uint32_t ResourceLoaderThread(void *pRM);
						
			mutable std::mutex m_rmThreadsShouldStopMutex;
			mutable std::condition_variable m_rmThreadsShouldStopCondVar;
			mutable bool m_bRMThreadsShouldStop;
			
			std::vector<std::shared_ptr<IResource>> m_toBeLoaded;
			std::vector<std::shared_ptr<IResource>> m_inMemory;
			std::vector<std::shared_ptr<IResource>> m_toBeUnloaded;	// to be released
			
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
