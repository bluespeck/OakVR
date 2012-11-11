
#include "BMPLoader.h"

namespace ro3d
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		RawImageData BMPLoader::GetRawImage(Buffer &fileBuffer)
		{
			RawImageData rawImageData;

			struct BMPMagicChars
			{
				char magicChars[2];
			} bmpMC;

			struct BMPHeader
			{				
				uint32_t size;
				uint32_t reserved;
				uint32_t imageDataOffset;
			} bmpHeader;
						
			fileBuffer.RewindForRead();
			fileBuffer.Read(&bmpMC, sizeof(BMPMagicChars));
			fileBuffer.Read(&bmpHeader, sizeof(BMPHeader));
			
			if(bmpMC.magicChars[0] == 'B' && bmpMC.magicChars[1] == 'M')
			{
				uint32_t dibHeaderSize;
				fileBuffer.Read(&dibHeaderSize, 4);
				
				switch(dibHeaderSize)
				{
				case 40:	// BITMAPINFOHEADER
					{
						// Read image properties
						struct BMPInfoHeader
						{
							int32_t width;
							int32_t height;
							uint16_t nplanes;
							uint16_t bitspp;
							uint32_t compress_type;
							uint32_t bmp_bytesz;
							int32_t hres;
							int32_t vres;
							uint32_t ncolors;
							uint32_t nimpcolors;
						} bmpInfoHeader;
						fileBuffer.Read(&bmpInfoHeader, sizeof(BMPInfoHeader));

						rawImageData.width = bmpInfoHeader.width;
						rawImageData.height = bmpInfoHeader.height;
						rawImageData.bitsPerPixel = (uint8_t)bmpInfoHeader.bitspp;
						uint32_t sizeInBytes = rawImageData.width * rawImageData.height * rawImageData.bitsPerPixel / 8;
						
						// Read pixel data
						rawImageData.m_imageData.CopyFromBuffer(fileBuffer, sizeInBytes); 

					}
					break;
				case 12:	// BITMAPCOREHEADER
					{
						// Read image properties
						struct BMPInfoHeader
						{
							uint16_t width;
							uint16_t height;
							uint16_t nplanes;
							uint16_t bitspp;
						} bmpInfoHeader;
						fileBuffer.Read(&bmpInfoHeader, sizeof(BMPInfoHeader));
						
						rawImageData.width = bmpInfoHeader.width;
						rawImageData.height = bmpInfoHeader.height;
						rawImageData.bitsPerPixel = (uint8_t)bmpInfoHeader.bitspp;
						uint32_t sizeInBytes = rawImageData.width * rawImageData.height * rawImageData.bitsPerPixel / 8;

						// Read pixel data
						rawImageData.m_imageData.CopyFromBuffer(fileBuffer, sizeInBytes); 
					}
					break;
				default:
					printf("Unsupported BMP file format");
					break;
				}
				
			}
			return rawImageData;
		}
	}
}
