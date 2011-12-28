
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RESOURCEMANAGER_H__
#define __OAK3D_INCLUDE_RESOURCEMANAGER_H__

#include <list>
#include <algorithm>

#include "Core/ResourceManager/IResource.h"
#include "Core/Utils/StringID.h"
#include "Core/Utils/Singleton.h"

namespace Oak3D
{
	namespace Core
	{
		class ResourceManager: public Singleton<ResourceManager>
		{
		public:
			void Initialize();

			template<typename ResourceType>
			ResourceType * GetResource(const StringId &id, IResource::AditionalInitParams *pAditionalInitParams = nullptr);
			void ReleaseResource(IResource *pRes);
			void ReleaseResource(const StringId &id);

			static void Stop() { m_bShouldStop = true; }

			ResourceManager();

		private:
			static uint32_t ResourceLoaderThread(void *pRM);

			std::list<IResource *> m_toBeLoaded;
			std::list<IResource *> m_inMemory;

			static bool m_bShouldStop;
		};

		// --------------------------------------------------------------------------------
		template<typename ResourceType>
		ResourceType * ResourceManager::GetResource(const StringId &id, IResource::AditionalInitParams *pAditionalInitParams)
		{
			{
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id.GetHashId() == id.GetHashId();
				});
				if(it != m_inMemory.end())
				{
					(*it)->m_refCount++;
					return dynamic_cast<ResourceType *>(*it);
				}
			}
			{
				auto it = std::find_if(m_toBeLoaded.begin(), m_toBeLoaded.end(), [&](IResource *pt)
				{
					return pt->m_id.GetHashId() == id.GetHashId();
				});
				if(it != m_toBeLoaded.end())
				{
					(*it)->m_refCount++;
					return dynamic_cast<ResourceType *>(*it);
				}
			}
			
			// Add new resource to the TO BE LOADED queue
			auto sp = new ResourceType();
			sp->Init(id, pAditionalInitParams);
			m_toBeLoaded.push_back(sp);
			return sp;
		}

	}
}



#endif