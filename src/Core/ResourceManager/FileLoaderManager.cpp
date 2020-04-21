#include "FileLoaderManager.h"
#include <algorithm>

namespace oakvr::core
{
	std::vector<sp<FileLoader>> &FileLoaderManager::GetFileLoaders()
	{
		static std::vector<sp<FileLoader>> s_fileLoaders;
		return s_fileLoaders;
	}

	auto FileLoaderManager::RegisterFileLoader(sp<FileLoader> pFileLoader) -> void
	{
		GetFileLoaders().push_back(pFileLoader);
	}
		
	auto FileLoaderManager::UnregisterFileLoader(sp<FileLoader> pFileLoader) -> void
	{
		auto &s_fileLoaders = GetFileLoaders();
		s_fileLoaders.erase(std::remove_if(std::begin(s_fileLoaders), std::end(s_fileLoaders), [&](const sp<FileLoader> &pFL)->bool{ return pFL == pFileLoader; }), s_fileLoaders.end());
	}
}