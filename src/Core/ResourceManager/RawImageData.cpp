#include "RawImageData.h"

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		RawImageData::RawImageData()
			: width(0), height(0), bitsPerPixel(4)
		{
			
		}

		// --------------------------------------------------------------------------------
		RawImageData::RawImageData(uint32_t sizeInBytes)
			: m_imageData(sizeInBytes)
		{
			
		}

		// --------------------------------------------------------------------------------
		RawImageData::RawImageData(uint32_t widthInPixels, uint32_t heightInPixels, uint8_t bitsPerPixel)
			: width(widthInPixels), height(heightInPixels), bitsPerPixel(bitsPerPixel)
		{
			uint32_t sizeInBytes = bitsPerPixel * width * height;
			m_imageData = Buffer(sizeInBytes);
		}

		// --------------------------------------------------------------------------------
		RawImageData::~RawImageData()
		{	
		}
	}
}
