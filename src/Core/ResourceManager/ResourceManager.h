
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RESOURCEMANAGER_H__
#define __OAK3D_INCLUDE_RESOURCEMANAGER_H__

#include <list>
#include <algorithm>

#include "Core/ResourceManager/IResource.h"
#include "Core/Utils/StringID.h"
#include "Core/Utils/Singleton.h"
#include "Core/Parallel/CriticalSection.h"

namespace Oak3D
{
	namespace Core
	{
		class ResourceManager: public Singleton<ResourceManager>
		{
		public:
			void Initialize();

			template<typename ResourceType>
			ResourceType * GetResource(const StringId &id, IResource::AdditionalInitParams *pAdditionalInitParams = nullptr);
			void ReleaseResource(IResource *pRes);
			void ReleaseResource(const StringId &id);

			static void Stop() { m_bShouldStop = true; }

			ResourceManager();
			
		private:
			static uint32_t ResourceLoaderThread(void *pRM);

			std::list<IResource *> m_toBeLoaded;
			std::list<IResource *> m_inMemory;
			CriticalSection m_loadCritSection;
			CriticalSection m_memoryCritSection;

			static bool m_bShouldStop;
		};

		// --------------------------------------------------------------------------------
		template<typename ResourceType>
		ResourceType * ResourceManager::GetResource(const StringId &id, IResource::AdditionalInitParams *pAditionalInitParams)
		{
			m_memoryCritSection.EnterCriticalSection();
			m_loadCritSection.EnterCriticalSection();
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
					m_memoryCritSection.LeaveCriticalSection();
					m_loadCritSection.LeaveCriticalSection();
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
					m_memoryCritSection.LeaveCriticalSection();
					m_loadCritSection.LeaveCriticalSection();
					return pRes;
				}
			}
			m_memoryCritSection.LeaveCriticalSection();
			m_loadCritSection.LeaveCriticalSection();
			// Add new resource to the TO BE LOADED queue
			auto sp = new ResourceType();
			sp->Init(id, pAditionalInitParams);
			m_loadCritSection.EnterCriticalSection();
			m_toBeLoaded.push_back(sp);
			m_loadCritSection.LeaveCriticalSection();
			return sp;
		}

	}
}



#endif