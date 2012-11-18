#pragma once

#include <vector>
#include <algorithm>

#include <mutex>
#include <thread>
#include <memory>
#include <condition_variable>

#include "ResourceManager/IResource.h"
#include "Utils/StringID.h"
#include "Utils/Singleton.h"
#include "Parallel/CriticalSection.h"
#include "Parallel/Thread.h"

namespace ro3d
{
	namespace Core
	{
		class ResourceManager: public ro3d::LLAPI::Singleton<ResourceManager>
		{
		public:
			void Initialize();

			template<typename ResourceType>
			ResourceType * GetResource(const StringId &id, IResource::AdditionalInitParams *pAdditionalInitParams = nullptr);
			void ReleaseResource(IResource *pRes);
			void ReleaseResource(const StringId &id);

			ResourceManager();
			~ResourceManager();
			
		private:
			static uint32_t ResourceLoaderThread(void *pRM);

			std::vector<IResource *> m_toBeLoaded;
			std::vector<IResource *> m_inMemory;
			std::vector<IResource *> m_toBeUnloaded;	//to be released
			
			std::mutex m_rmThreadsShouldStopMutex;
			std::condition_variable m_rmThreadsShouldStopCondVar;
			bool m_bRMThreadsShouldStop;
			
			std::mutex m_loadMutex;
			std::condition_variable m_loadCondVar;

			std::mutex m_unloadMutex;
			std::condition_variable m_unloadCondVar;


			std::unique_ptr<std::thread> m_pRMLoadThread;
			std::unique_ptr<std::thread> m_pRMUnloadThread;
		};

		// --------------------------------------------------------------------------------
		template<typename ResourceType>
		ResourceType * ResourceManager::GetResource(const StringId &id, IResource::AdditionalInitParams *pAditionalInitParams)
		{
			/*m_pMemoryCritSection->EnterCriticalSection();
			m_pLoadCritSection->EnterCriticalSection();
			if(m_inMemory.size() > 0)
			{
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id == id;
				});
				if(it != m_inMemory.end())
				{
					(*it)->m_refCount++;
					ResourceType *pRes = dynamic_cast<ResourceType *>(*it);
					m_pMemoryCritSection->LeaveCriticalSection();
					m_pLoadCritSection->LeaveCriticalSection();
					return pRes;
				}
			}
						
			if(m_toBeLoaded.size() > 0)
			{
				auto it = std::find_if(m_toBeLoaded.begin(), m_toBeLoaded.end(), [&](IResource *pt)
				{
					return pt->m_id == id;
				});
				if(it != m_toBeLoaded.end())
				{
					(*it)->m_refCount++;
					ResourceType *pRes = dynamic_cast<ResourceType *>(*it);
					m_pMemoryCritSection->LeaveCriticalSection();
					m_pLoadCritSection->LeaveCriticalSection();
					return pRes;
				}
			}
			m_pMemoryCritSection->LeaveCriticalSection();
			m_pLoadCritSection->LeaveCriticalSection();
			// Add new resource to the TO BE LOADED queue
			auto sp = new ResourceType();
//			sp->Init(id, pAditionalInitParams);
//			m_pLoadCritSection->EnterCriticalSection();
//			m_toBeLoaded.push_back(sp);
//			m_pLoadCritSection->LeaveCriticalSection();
//			sp->m_refCount++;
			return sp;
			*/
			return nullptr;
		}

	}
}
