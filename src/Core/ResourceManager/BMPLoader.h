#pragma once

#include <cstdint>
#include <string>

#include "RawImageData.h"

namespace oakvr
{
	namespace core
	{
		class BMPLoader
		{
		public:
			static RawImageData GetRawImage(Buffer &fileBuffer);
		};
	}
}

