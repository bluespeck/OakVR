
#include <cassert>
#include <memory>
#include <thread>

#include "ResourceManager.h"
#include "IResource.h"

using std::shared_ptr;

namespace ro3d
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		: m_bRMThreadsShouldStop(false)
		{
			m_pRMLoadThread.reset(new std::thread([this]
			{
				while(true)
				{
					{
						// check if we have any resources to be loaded
						std::unique_lock<std::mutex> ul(m_toBeLoadedMutex);
						m_toBeLoadedCondVar.wait_for(ul, std::chrono::milliseconds(50), [=]()->bool{ return m_toBeLoaded.size() > 0; } );
						while(m_toBeLoaded.size())
						{
							auto e = m_toBeLoaded.back();
							m_toBeLoaded.pop_back();							
							{
								std::lock_guard<std::mutex> lg(m_inMemoryMutex);
								m_inMemory.push_back(e);
							}
							e->_Load();
							e->SetState(ResourceState::loading);
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
			}));
			m_pRMUnloadThread.reset(new std::thread([this]
			{
				while(true)
				{
					{
						std::unique_lock<std::mutex> ul(m_unloadMutex);
						m_unloadCondVar.wait_for(ul, std::chrono::milliseconds(50), [=]()->bool{ return m_toBeUnloaded.size() > 0; } );
						while(m_toBeUnloaded.size())
						{
							auto e = m_toBeUnloaded.back();
							e->SetState(ResourceState::unloading);
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
			}));
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
		void ResourceManager::ReleaseResource(std::shared_ptr<IResource> pRes)
		{
			assert(pRes->IsReady());
			std::lock_guard<std::mutex> lg(m_inMemoryMutex);

			typedef decltype(*m_inMemory.begin()) ElemType;
			auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](ElemType &rpRes)
			{
				return rpRes->GetId() == pRes->GetId();
			});
			if(it != m_inMemory.end())
			{
				m_inMemory.erase(it);
			}
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(const StringId &id)
		{
			std::lock_guard<std::mutex> lg(m_inMemoryMutex);

			typedef decltype(*m_inMemory.begin()) ElemType;
			auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](ElemType &pRes)
			{
				return pRes->GetId() == id;
			});
			if(it != m_inMemory.end())
			{
				m_inMemory.erase(it);
			}
		}

		// --------------------------------------------------------------------------------
		std::shared_ptr<IResource> ResourceManager::GetResource(const StringId &id)
		{
			auto compareFct = [](std::shared_ptr<IResource> e1, std::shared_ptr<IResource> e2)
				{
					return e1->GetId() < e2->GetId();
				};				
			{
				std::lock_guard<std::mutex> lg(m_inMemoryMutex);
				auto endIt = m_inMemory.end();
				auto range = std::equal_range(m_inMemory.begin(), endIt, std::make_shared<EmptyResource>(id), compareFct);
				if(range.first != range.second)
					return *range.first;
			}
			{
				std::unique_lock<std::mutex> ul(m_toBeLoadedMutex);
				auto startIt = m_toBeLoaded.begin();
				auto endIt = m_toBeLoaded.end();
				auto range = std::equal_range(startIt, endIt, std::make_shared<EmptyResource>(id), compareFct);
				if(range.first != range.second)
					return *range.first;

				// if we get to this point, we need to load the resource
				auto it = std::lower_bound(startIt, endIt, std::make_shared<EmptyResource>(id), compareFct);
				m_toBeLoaded.insert(it,std::make_shared<EmptyResource>(id));
			}
			return nullptr;
		}
	} // namespace Core
} // namespace ro3d
