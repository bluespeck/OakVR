
#include <cassert>
#include <memory>
#include <thread>

#include "ResourceManager.h"
#include "FileLoaderManager.h"
#include "FileIO/Directory.h"
#include "FileIO/File.h"
#include "FileIO/Path.h"
#include "Log/Log.h"
#include "Utils/Types.h"


namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		ResourceManager::ResourceManager()
		//: m_bRMThreadsShouldStop(false)
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

		auto ResourceManager::AddPathsFromFolder(const std::string &path)->bool
		{
			core::io::Directory dir(path);
			auto files = dir.GetFileList(true);
			if (files.size() == 0)
			{
				oakvr::Log::Error("Could not load files from path \"%s\" !", path.c_str());
				return false;
			}
			// retrieve path id and add to path map
			for (auto &e : files)
			{
				auto stem = core::io::path::GetStem(e);
				if (stem.size())
				{
					m_mapPaths[stem] = e;
				}
			}

			return true;
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
		void ResourceManager::CreateResourceFromMemory(const std::string &id, const MemoryBuffer &buffer)
		{
			auto it = m_mapResources.find(id);
			if (it != std::end(m_mapResources))
			{
				Log::Warning("Trying to create a resource with an id that already exists! (Resource id = %s)", id.c_str());
				return;
			}

			m_mapResources.emplace(id, std::make_shared<MemoryBuffer>(buffer));
		}

		// --------------------------------------------------------------------------------
		sp<MemoryBuffer> ResourceManager::GetResource(const std::string &id)
		{
			auto it = m_mapResources.find(id);
			if (it != std::end(m_mapResources))
			{
				// we have the buffer for this resource id in our cache; just return the buffer
				return it->second;
			}
			else
			{
				// see if there is a file in our index that matches the name of the resource and load that one
				// this can fail superbly if multiple files have the same name so keep an eye on this
				auto it = m_mapPaths.find(id);
				if (it != std::end(m_mapPaths) && oakvr::core::io::File::Exists(it->second))
				{
					oakvr::core::io::File f(it->second);
					f.Open(oakvr::core::io::File::FileOpenMode::read);
					auto pMemBuff = std::make_shared<MemoryBuffer>(f.Size());
					f.Read(pMemBuff->GetDataPtr(), pMemBuff->Size(), pMemBuff->Size());
					f.Close();

					for (sp<FileLoader> &pLoader : FileLoaderManager::GetFileLoaders())
					{
						if (pLoader->CanLoad(*pMemBuff))
						{
							auto pResMemBuf = std::make_shared<MemoryBuffer>(pLoader->GetResourceData(*pMemBuff));
							m_mapResources[id] = pResMemBuf;
							return pResMemBuf;
						}
					}
					m_mapResources[id] = pMemBuff;
					return pMemBuff;
				}
			}

			Log::Warning("Could not retrieve resource %s", id.c_str());
			return nullptr;
		}
		
	} // namespace core
} // namespace oakvr
