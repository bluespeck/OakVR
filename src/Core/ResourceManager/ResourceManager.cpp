
#include <cassert>
#include <memory>
#include <thread>

#include "ResourceManager.h"
#include "FileIO/Directory.h"
#include "FileIO/Path.h"
#include "Log/Log.h"

using std::shared_ptr;

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		: m_bRMThreadsShouldStop(false)
		{
			// ------------------------------------------
			// Defining the resource loding worker thread
			/*
			m_pRMLoadThread.reset(new std::thread([this]()
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
								//m_mapResources[m_inMemory.push_back(e);
							}
							//e->_Load();
							//e->SetState(ResourceState::loading);
						}
					}

					{
						// sleep for 50 milliseconds or end the thread
						std::unique_lock<std::mutex> ul(m_rmThreadsShouldStopMutex);
						m_rmThreadsShouldStopCondVar.wait_for(ul, std::chrono::milliseconds(50),[=]()->bool{ return !m_bRMThreadsShouldStop; });
						if(m_bRMThreadsShouldStop)
							return;
					}
				}
			}));*/
			/*
			// --------------------------------------------
			// Defining the resource unloding worker thread
			m_pRMUnloadThread.reset(new std::thread([this]()
			{
				while(true)
				{
					{
						std::unique_lock<std::mutex> ul(m_unloadMutex);
						m_unloadCondVar.wait_for(ul, std::chrono::milliseconds(50), [=]()->bool{ return m_toBeUnloaded.size() > 0; } );
						
						while(m_toBeUnloaded.size())
						{
							auto e = m_toBeUnloaded.back();
							m_toBeUnloaded.pop_back();
						//	e->SetState(ResourceState::unloading);
						}
					}

					{
						// sleep for 50 milliseconds or end the thread
						std::unique_lock<std::mutex> ul(m_rmThreadsShouldStopMutex);
						m_rmThreadsShouldStopCondVar.wait_for(ul, std::chrono::milliseconds(50),[=]()->bool{ return !m_bRMThreadsShouldStop; });
						if(m_bRMThreadsShouldStop)
							return;
					}
				}
			}));
			*/
		}

		// --------------------------------------------------------------------------------
		ResourceManager::~ResourceManager()
		{/*
			{
				std::lock_guard<std::mutex> lg(m_rmThreadsShouldStopMutex);
				m_bRMThreadsShouldStop = true;
				m_rmThreadsShouldStopCondVar.notify_all();
			}
				

			//m_pRMUnloadThread->join();
			//m_pRMLoadThread->join();
			
			//for(auto e:m_inMemory)
			//	e->Release();
			//for(auto e:m_toBeUnloaded)
			//	e->Release();
			*/
		} 

		void ResourceManager::AddPathsFromFolder(const std::string &path)
		{
			core::io::Directory dir(path);
			auto files = dir.GetFileList(true);
			// retrieve path id and add to path map
			for (auto &e : files)
			{
				auto stem = core::io::path::GetStem(e);
				if (stem.size())
				{
					m_mapPaths[stem] = e;
				}
			}
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::ReleaseResource(const std::string &id)
		{
			/*
			std::lock_guard<std::mutex> mlg(m_inMemoryMutex);

			typedef decltype(*m_inMemory.begin()) ElemType;
			auto it = std::find_if(m_inMemory.begin(), m_inMemory.end(), [&](ElemType &pRes)
			{
				return pRes->GetId() == id;
			});
			if(it != m_inMemory.end())
			{
				{
					std::lock_guard<std::mutex> ulg(m_unloadMutex);
					m_toBeUnloaded.push_back(*it);
				}
				m_inMemory.erase(it);
			}
			*/
		}

		// --------------------------------------------------------------------------------
		std::shared_ptr<MemoryBuffer> ResourceManager::GetResource(const std::string &id)
		{
			/*
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
				m_toBeLoaded.insert(it, std::make_shared<EmptyResource>(id));
			}
			return std::make_shared<EmptyResource>(id);
			*/
			return std::make_shared<MemoryBuffer>();
		}
		
	} // namespace core
} // namespace oakvr
