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
			auto it = std::find(std::begin(s_fileLoaders), std::end(s_fileLoaders), pFileLoader);
			if (it != s_fileLoaders.end())
			{
				s_fileLoaders.erase(it);
			}
		}
	}
}