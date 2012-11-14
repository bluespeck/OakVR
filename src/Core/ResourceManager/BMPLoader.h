#pragma once

#include <cstdint>
#include <string>

#include "RawImageData.h"

namespace ro3d
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

