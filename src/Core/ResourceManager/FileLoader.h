#pragma once

#include "Utils/Buffer.h"

namespace oakvr::core
{
	class FileLoader
	{
	public:
		FileLoader(){}
		virtual ~FileLoader();

		virtual MemoryBuffer GetResourceData(const MemoryBuffer &fileBuffer) = 0;
		virtual auto CanLoad(const MemoryBuffer &filebuffer) -> bool = 0;
			
	};
}