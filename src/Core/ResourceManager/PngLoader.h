#pragma once

#include "FileLoader.h"
#include "Utils/Buffer.h"

#include <cstdint>
#include <string>

namespace oakvr
{
	namespace core
	{
		class PngLoader : public FileLoader
		{
		public:
			MemoryBuffer GetResourceData(const MemoryBuffer &fileBuffer);
			virtual bool CanLoad(const MemoryBuffer &filebuffer);
		};
	}
}