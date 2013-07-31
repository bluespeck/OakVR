#pragma once

#include <cstdint>
#include <string>

#include "RawImageData.h"

namespace oakvr
{
	namespace Core
	{
		class BMPLoader
		{
		public:
			static RawImageData GetRawImage(Buffer &fileBuffer);
		};
	}
}

