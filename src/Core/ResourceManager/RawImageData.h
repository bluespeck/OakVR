#pragma once

#include <cstdint>

#include "Buffer.h"

namespace oakvr
{
	namespace core
	{
		struct RawImageData
		{
			RawImageData();
			RawImageData(uint32_t sizeInBytes);
			RawImageData(uint32_t widthInPixels, uint32_t heightInPixels, uint8_t bitsPerPixel);
			~RawImageData();

			uint32_t GetSizeInBytes() { return m_imageData.GetSize(); }

			Buffer m_imageData;
			uint32_t width;
			uint32_t height;
			uint8_t bitsPerPixel;
		};
	}
}

