#pragma once

#include "FileLoader.h"

#include <vector>
#include <memory>

namespace oakvr
{
	namespace core
	{
		class FileLoaderManager
		{
		public:
			static void RegisterFileLoader(std::shared_ptr<FileLoader> pFileLoader);
			static void UnregisterFileLoader(std::shared_ptr<FileLoader> pFileLoader);
			static std::vector<std::shared_ptr<FileLoader>> &GetFileLoaders();
		};
	}
}