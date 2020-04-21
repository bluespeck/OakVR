#pragma once

#include <cstdint>
#include <string>

#include "RawImageData.h"

namespace oakvr::core
{
	class BMPLoader
	{
	public:
		static MemoryBuffer GetRawImage(const MemoryBuffer &fileBuffer);
	};
}

