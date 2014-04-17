#include "PngLoader.h"

#include "png.h"
#include "pngstruct.h"

#include "Utils/BufferReader.h"
#include "Utils/BufferWriter.h"
#include "RawImageData.h"

void PngReadFn(png_structp pPng, png_bytep outBytes, png_size_t bytecountToRead);

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		MemoryBuffer PngLoader::GetResourceData(const MemoryBuffer &fileBuffer)
		{
			png_structp pPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
			
			png_infop pInfo = png_create_info_struct(pPng);

			BufferReader<std::common_type<decltype(fileBuffer)>::type::value_type, uint32_t> fileBufferReader(fileBuffer);
			png_set_read_fn(pPng, (void *)&fileBufferReader, PngReadFn);

			png_read_info(pPng, pInfo);

			png_uint_32 width = 0;
			png_uint_32 height = 0;
			int bitDepth = 0;
			int colorType = -1;

			png_get_IHDR(pPng, pInfo, &width, &height, &bitDepth, &colorType, nullptr, nullptr, nullptr);
			
			RawImageData imageData;
			imageData.width = width;
			imageData.height = height;
			imageData.bitsPerPixel = bitDepth;
			switch (colorType)
			{
			case PNG_COLOR_TYPE_RGB:
				imageData.pixelFormat = RawImageData::PixelFormat::rgb;
				imageData.bitsPerPixel *= 3;
				break;
			case PNG_COLOR_TYPE_RGBA:
				imageData.pixelFormat = RawImageData::PixelFormat::rgba;
				imageData.bitsPerPixel *= 4;
				break;
			default:
				imageData.pixelFormat = RawImageData::PixelFormat::unknown;
				break;
			}
			
			const png_uint_32 bytesPerRow = png_get_rowbytes(pPng, pInfo);
			imageData.pixelBuffer = MemoryBuffer(bytesPerRow * imageData.height);
			png_bytep pRow = imageData.pixelBuffer.GetDataPtr();
			for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex, pRow += bytesPerRow)
				png_read_row(pPng, pRow, nullptr);


			// serialize image data
			MemoryBuffer rawImageData(sizeof(imageData.width) + sizeof(imageData.height) + sizeof(imageData.bitsPerPixel) + sizeof(imageData.pixelFormat) + imageData.pixelBuffer.Size());

			BufferWriter<MemoryBuffer::value_type, uint32_t> bufferWriter(rawImageData);
			bufferWriter.Write(imageData.width);
			bufferWriter.Write(imageData.height);
			bufferWriter.Write(imageData.bitsPerPixel);
			bufferWriter.Write(imageData.pixelFormat);
			bufferWriter.Write(imageData.pixelBuffer.GetDataPtr(), imageData.pixelBuffer.Size());

			return rawImageData;
		}

		// --------------------------------------------------------------------------------
		bool PngLoader::CanLoad(const MemoryBuffer &fileBuffer)
		{
			auto p = fileBuffer.GetDataPtr();

			return fileBuffer.Size() > 8 && p[0] == 137 && p[1] == 80 && p[2] == 78 && p[3] == 71
				&& p[4] == 13 && p[5] == 10 && p[6] == 26 && p[7] == 10;
		}
	}
}

// --------------------------------------------------------------------------------
void PngReadFn(png_structp pPng, png_bytep outBytes, png_size_t bytecountToRead)
{
	oakvr::core::BufferReader<uint8_t, uint32_t> *pReader = static_cast<oakvr::core::BufferReader<uint8_t, uint32_t>*>(pPng->io_ptr);
	pReader->Read(outBytes, bytecountToRead);
}