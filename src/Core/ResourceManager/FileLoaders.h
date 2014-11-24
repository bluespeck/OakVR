#pragma once

#include "PngLoader.h"
#include "OakVRLoader.h"
#include "FileLoaderManager.h"
#include "Utils/Types.h"
#include <memory>

namespace oakvr
{
	namespace core
	{
		inline void InitializeFileLoaders()
		{
			FileLoaderManager::RegisterFileLoader(sp<FileLoader>(new PngLoader()));
			FileLoaderManager::RegisterFileLoader(sp<FileLoader>(new OakVRLoader()));
		}
	}
}