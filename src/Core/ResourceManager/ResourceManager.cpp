
#include <cassert>
#include <memory>
#include <thread>

#include "ResourceManager.h"
#include "IResource.h"
#include "Parallel/Thread.h"

using std::shared_ptr;

namespace ro3d
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		: m_bRMThreadsShouldStop(false)
		, m_pRMLoadThread(new std::thread([this]
			{
				while(true)
				{
					{
						std::unique_lock<std::mutex> ul(m_loadMutex);
						m_loadCondVar.wait_for(ul, std::chrono::milliseconds(50), [=]()->bool{ return m_toBeLoaded.size() > 0; } );
						for(auto e: m_toBeLoaded)
						{
							m_inMemory.push_back(e);
							e->Load();
							e->SetState(IResource::ResourceState::loading);
						}
					}

					{
						// sleep for 50 milliseconds or end the thread
						std::unique_lock<std::mutex> ul(m_rmThreadsShouldStopMutex);
						m_rmThreadsShouldStopCondVar.wait_for(ul, std::chrono::milliseconds(50),[=]()->bool{ return !m_bRMThreadsShouldStop; });
						if(m_bRMThreadsShouldStop)
							break;
					}
				}
			}))
		, m_pRMUnloadThread(new std::thread([this]
			{
				while(true)
				{
					{
						std::unique_lock<std::mutex> ul(m_unloadMutex);
						m_unloadCondVar.wait_for(ul, std::chrono::milliseconds(50), [=]()->bool{ return m_toBeUnloaded.size() > 0; } );
						while(m_toBeUnloaded.size())
						{
							auto e = m_toBeUnloaded.back();
							e->SetState(IResource::ResourceState::unloading);
							e->Release();
							m_toBeUnloaded.pop_back();
						}
					}

					{
						// sleep for 50 milliseconds or end the thread
						std::unique_lock<std::mutex> ul(m_rmThreadsShouldStopMutex);
						m_rmThreadsShouldStopCondVar.wait_for(ul, std::chrono::milliseconds(50),[=]()->bool{ return !m_bRMThreadsShouldStop; });
						if(m_bRMThreadsShouldStop)
							break;
					}
				}
			}))
		{
		}

		// --------------------------------------------------------------------------------
		ResourceManager::~ResourceManager()
		{
			{
				std::lock_guard<std::mutex> lg(m_rmThreadsShouldStopMutex);
				m_bRMThreadsShouldStop = true;
			}
			m_rmThreadsShouldStopCondVar.notify_all();

			m_pRMLoadThread->join();
			m_pRMUnloadThread->join();
			
			for(auto e:m_inMemory)
				e->Release();
			for(auto e:m_toBeUnloaded)
				e->Release();
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(IResource *pRes)
		{
			auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
			{
				return pt->m_id == pRes->m_id;
			});
			if(it != m_inMemory.end())
			{
				--(*it)->m_refCount;
				
			}
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(const StringId &id)
		{
			auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](IResource *pt)
			{
				return pt->m_id.GetHashId() == id.GetHashId();
			});
			if(it != m_inMemory.end())
			{
				--(*it)->m_refCount;
				
			}
		}
	} // namespace Core
} // namespace ro3d
