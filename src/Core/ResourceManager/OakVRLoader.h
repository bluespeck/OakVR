#pragma once

#include "FileLoader.h"
#include "Utils/Buffer.h"

namespace oakvr
{
	namespace core
	{
		class OakVRLoader : public FileLoader
		{
		public:
			MemoryBuffer GetResourceData(const MemoryBuffer &fileBuffer);
			virtual bool CanLoad(const MemoryBuffer &filebuffer);
		};
	}
}