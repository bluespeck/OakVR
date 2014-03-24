#pragma once

#include "PngLoader.h"
#include "FileLoaderManager.h"

#include <memory>

namespace oakvr
{
	namespace core
	{
		inline void InitializeFileLoaders()
		{
			FileLoaderManager::RegisterFileLoader(std::shared_ptr<FileLoader>(new PngLoader()));
		}
	}
}