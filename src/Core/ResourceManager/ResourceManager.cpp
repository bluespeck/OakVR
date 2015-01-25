
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
		
		{
			
		}

		// --------------------------------------------------------------------------------
		ResourceManager::~ResourceManager()
		{
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
		void ResourceManager::ReleaseResource(const StringId &id)
		{
			
		}

		// --------------------------------------------------------------------------------
		void ResourceManager::CreateResourceFromMemory(const StringId &id, const MemoryBuffer &buffer)
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
		sp<MemoryBuffer> ResourceManager::GetResource(const StringId &id)
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
