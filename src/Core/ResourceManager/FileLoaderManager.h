#pragma once

#include "FileLoader.h"
#include "Utils/Types.h"

#include <vector>
#include <memory>

namespace oakvr
{
	namespace core
	{
		class FileLoaderManager
		{
		public:
			static void RegisterFileLoader(sp<FileLoader> pFileLoader);
			static void UnregisterFileLoader(sp<FileLoader> pFileLoader);
			static std::vector<sp<FileLoader>> &GetFileLoaders();
		};
	}
}