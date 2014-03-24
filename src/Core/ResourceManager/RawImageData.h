#pragma once

#include <cstdint>

#include "Utils/Buffer.h"

namespace oakvr
{
	namespace core
	{
		struct RawImageData
		{
			uint32_t width;
			uint32_t height;
			uint32_t bitsPerPixel;
			enum class PixelFormat
			{
				unknown,
				rgba,
				rgb,
			}pixelFormat;
			MemoryBuffer pixelBuffer;
		};
	}
}

