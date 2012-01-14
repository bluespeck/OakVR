
#include "ResourceManager.h"
#include "IResource.h"
#include "Core/Parallel/Thread.h"

using std::shared_ptr;

namespace Oak3D
{
	namespace Core
	{
		bool ResourceManager::m_bShouldStop = false;

		// --------------------------------------------------------------------------------
		uint32_t ResourceManager::ResourceLoaderThread(void *pResMgr)
		{
			ResourceManager *pRM = static_cast<ResourceManager*>(pResMgr);
			
			while(!pRM->m_bShouldStop)
			{
				IResource *pRes = nullptr;
				pRM->m_loadCritSection.EnterCriticalSection();
				if(pRM->m_toBeLoaded.size())
				{
					pRes = pRM->m_toBeLoaded.front();
				}
				pRM->m_loadCritSection.LeaveCriticalSection();

				if(pRes)
				{
					pRes->Load();
					
					pRM->m_memoryCritSection.EnterCriticalSection();
					pRM->m_loadCritSection.EnterCriticalSection();
					pRM->m_toBeLoaded.pop_front();
					pRM->m_inMemory.push_back(pRes);
					pRM->m_loadCritSection.LeaveCriticalSection();
					pRM->m_memoryCritSection.LeaveCriticalSection();
				}
			}
			return 0;
		}

		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		{
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::Initialize()
		{
			new Thread(ResourceLoaderThread, this);
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(IResource *pRes)
		{
			{
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id == pRes->m_id;
				});
				if(it != m_inMemory.end())
				{
					if(--(*it)->m_refCount <= 0)
					{
						IResource *p = *it;
						m_inMemory.erase(it);
						p->Release();
						delete p;
					}
				}
			}
			
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(const StringId &id)
		{
			{
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id.GetHashId() == id.GetHashId();
				});
				if(it != m_inMemory.end())
				{
					if(--(*it)->m_refCount <= 0)
					{
						IResource *p = *it;
						m_inMemory.erase(it);
						p->Release();
						delete p;
					}
				}
			}
		}
	} // namespace Core
} // namespace Oak3D
