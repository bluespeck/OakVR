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

namespace oakvr::core
{
	class ResourceManager
	{
	public:
		auto Initialize() -> void;

		auto CreateResourceFromMemory(const StringId &id, const MemoryBuffer &buffer) -> void;
		auto GetResource(const StringId &id) -> sp<MemoryBuffer>;
			
		auto ReleaseResource(const StringId &id) -> void;

		ResourceManager();
		~ResourceManager();
		
		auto AddPathsFromFolder(const std::string &path)->bool;
			
	private:
		std::unordered_map<StringId, std::shared_ptr<MemoryBuffer>> m_mapResources;
		std::unordered_map<StringId, std::string> m_mapPaths;

	};
}
