#pragma once

#include "FileLoader.h"
#include "Utils/Buffer.h"

namespace oakvr::core
{
	class PngLoader : public FileLoader
	{
	public:
		auto GetResourceData(const MemoryBuffer &fileBuffer) -> MemoryBuffer;
		virtual auto CanLoad(const MemoryBuffer &filebuffer) -> bool;
	};
}