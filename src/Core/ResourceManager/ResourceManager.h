#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>

#include <memory>
#include <unordered_map>
#include <vector>

#include "ResourceManager/IResource.h"
#include "ResourceManager/EmptyResource.h"
#include "Utils/StringId.h"
#include "Utils/Singleton.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"

namespace oakvr
{
	namespace core
	{
		class ResourceManager
		{
		public:
			void Initialize();

			void CreateResourceFromMemory(const StringId &id, const MemoryBuffer &buffer);
			sp<MemoryBuffer> GetResource(const StringId &id);
			
			void ReleaseResource(const StringId &id);

			ResourceManager();
			~ResourceManager();
		
			auto AddPathsFromFolder(const std::string &path)->bool;
			
		private:
			std::unordered_map<StringId, std::shared_ptr<MemoryBuffer>> m_mapResources;
			std::unordered_map<StringId, std::string> m_mapPaths;

		};
	}
}
