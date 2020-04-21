#pragma once

#include "FileLoader.h"
#include "Utils/Types.h"

#include <vector>
#include <memory>

namespace oakvr::core
{
	class FileLoaderManager
	{
	public:
		static auto RegisterFileLoader(sp<FileLoader> pFileLoader) -> void;
		static auto UnregisterFileLoader(sp<FileLoader> pFileLoader) -> void;
		static std::vector<sp<FileLoader>> &GetFileLoaders();
	};
}