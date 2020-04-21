#pragma once

#include "PngLoader.h"
#include "OakVRLoader.h"
#include "FileLoaderManager.h"
#include "Utils/Types.h"
#include <memory>

namespace oakvr::core
{
	inline auto InitializeFileLoaders() -> void
	{
		FileLoaderManager::RegisterFileLoader(sp<FileLoader>(new PngLoader()));
		FileLoaderManager::RegisterFileLoader(sp<FileLoader>(new OakVRLoader()));
	}
}