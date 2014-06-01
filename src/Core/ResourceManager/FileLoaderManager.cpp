#include "FileLoaderManager.h"
#include <algorithm>

namespace oakvr
{
	namespace core
	{
		std::vector<std::shared_ptr<FileLoader>> &FileLoaderManager::GetFileLoaders()
		{
			static std::vector<std::shared_ptr<FileLoader>> s_fileLoaders;
			return s_fileLoaders;
		}

		void FileLoaderManager::RegisterFileLoader(std::shared_ptr<FileLoader> pFileLoader)
		{
			GetFileLoaders().push_back(pFileLoader);
		}
		
		void FileLoaderManager::UnregisterFileLoader(std::shared_ptr<FileLoader> pFileLoader)
		{
			auto &s_fileLoaders = GetFileLoaders();
			std::remove_if(std::begin(s_fileLoaders), std::end(s_fileLoaders), [&](const std::shared_ptr<FileLoader> &pFL)->bool{ return pFL == pFileLoader; });
		}
	}
}