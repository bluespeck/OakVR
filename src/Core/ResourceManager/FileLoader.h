#pragma once

#include "Utils/Buffer.h"

namespace oakvr
{
	namespace core
	{
		class FileLoader
		{
		public:
			FileLoader(){}
			virtual ~FileLoader();

			virtual MemoryBuffer GetResourceData(const MemoryBuffer &fileBuffer) = 0;
			virtual bool CanLoad(const MemoryBuffer &filebuffer) = 0;
			
		};
	}
}