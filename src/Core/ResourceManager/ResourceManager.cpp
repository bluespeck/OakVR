
#include <cassert>

#include "ResourceManager.h"
#include "IResource.h"
#include "Core/Parallel/Thread.h"

using std::shared_ptr;

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		uint32_t ResourceManager::ResourceLoaderThread(void *pResMgr)
		{
			ResourceManager *pRM = static_cast<ResourceManager*>(pResMgr);
			
			while(pRM && !pRM->m_bLoaderThreadShouldStop)
			{
				IResource *pRes = nullptr;
				pRM->m_pLoadCritSection->EnterCriticalSection();
				uint32_t ss = pRM->m_toBeLoaded.size();
				if(ss)
				{
					pRes = pRM->m_toBeLoaded.front();
				}
				pRM->m_pLoadCritSection->LeaveCriticalSection();

				if(pRes)
				{
					pRes->Load();
					
					pRM->m_pMemoryCritSection->EnterCriticalSection();
					pRM->m_pLoadCritSection->EnterCriticalSection();
					pRM->m_toBeLoaded.pop_front();
					pRM->m_inMemory.push_back(pRes);
					pRM->m_pLoadCritSection->LeaveCriticalSection();
					pRM->m_pMemoryCritSection->LeaveCriticalSection();
				}
				if(ss <= 1)
					Core::Thread::Sleep(150);
			}
			return 0;
		}

		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		: m_bLoaderThreadShouldStop(false)
		{
			m_pLoadCritSection = new CriticalSection();
			m_pMemoryCritSection = new CriticalSection();
		}

		// --------------------------------------------------------------------------------
		ResourceManager::~ResourceManager()
		{
			m_bLoaderThreadShouldStop = true;
			m_pLoaderThread->Join();
			delete m_pLoaderThread;
			delete m_pLoadCritSection;
			delete m_pMemoryCritSection;

			for(auto it = m_inMemory.begin(); it != m_inMemory.end(); ++it)
			{
				(*it)->Release();
				delete *it;
			}
			m_inMemory.clear();

		}

		// --------------------------------------------------------------------------------
		void ResourceManager::Initialize()
		{
			m_pLoaderThread = new Thread(ResourceLoaderThread, this);
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(IResource *pRes)
		{
			{
				m_pMemoryCritSection->EnterCriticalSection();
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id == pRes->m_id;
				});
				if(it != m_inMemory.end())
				{
					--(*it)->m_refCount;
					
				}
				m_pMemoryCritSection->LeaveCriticalSection();
			}
			
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(const StringId &id)
		{
			{
				m_pMemoryCritSection->EnterCriticalSection();
				auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
				{
					return pt->m_id.GetHashId() == id.GetHashId();
				});
				if(it != m_inMemory.end())
				{
					--(*it)->m_refCount;
					
				}
				m_pMemoryCritSection->LeaveCriticalSection();
			}
		}
	} // namespace Core
} // namespace Oak3D
