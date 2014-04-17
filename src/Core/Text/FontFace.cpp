#include "FontFace.h"
#include "Utils/Buffer.h"
#include "ResourceManager/RawImageData.h"
#include "Utils/BufferWriter.h"
#include "Math/MathUtils.h"
#include "Log/Log.h"


#include <array>
#include <string>
#include <memory>
#include <algorithm>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace oakvr
{
	namespace core
	{
		namespace text
		{
			// --------------------------------------------------------------------------------
			FontFace::FontFace(FT_LibraryRec_ *pFTLib, std::shared_ptr<MemoryBuffer> pFontFileBuffer, std::string fontFaceName /* = "" */)
			{
				FT_Face fontFace;
				FT_Error err = FT_New_Memory_Face(pFTLib, pFontFileBuffer->GetDataPtr(), pFontFileBuffer->Size(), 0, &fontFace);
				if (!err)
				{
					m_pFTFace = fontFace;
					if (!fontFaceName.length())
						m_name = std::string(m_pFTFace->family_name) + " " + m_pFTFace->style_name;
					else
						m_name = fontFaceName;

				}
				else
				{
					m_name = fontFaceName;
					Log::PrintError("Could not load font face %s", fontFaceName.c_str());
					return;
				}
				
				m_buff = RenderGlyphs();
			}

			// --------------------------------------------------------------------------------
			MemoryBuffer FontFace::RenderGlyphs()
			{
				FT_GlyphSlot slot = m_pFTFace->glyph;
				int scale = 8;
				FT_Set_Char_Size(m_pFTFace, scale * 64, 0, 300, 0);

				// upper left corner of the texture?
				int penX = 0;
				uint32_t maxRows = 0;
				for (char i = 32, k = 0; i < 127; ++i, ++k)
				{
					FT_Error err = FT_Load_Char(m_pFTFace, i, FT_LOAD_RENDER);
					if (err)
					{
						Log::PrintWarning("Could not load glyph for character code %d ('%c').", i, i);
						continue;
					}
					if (maxRows < slot->bitmap.rows)
						maxRows = slot->bitmap.rows;
					penX += slot->advance.x >> 6; // 1/64s of a pixel
				}

				m_textureWidth = oakvr::math::NextPowerOfTwo(penX);
				m_textureHeight = oakvr::math::NextPowerOfTwo(maxRows);

				MemoryBuffer buff(m_textureWidth * m_textureHeight * sizeof(uint8_t)); // uint8_t corresponding to GRAYS
				MemoryBuffer::value_type *pBuff = buff.GetDataPtr();
				memset(pBuff, 0, buff.Size());
				uint32_t accumulatedWidth = 0;
				for (char i = 32, k = 0; i < 127; ++i, ++k)
				{
					FT_Error err = FT_Load_Char(m_pFTFace, i, FT_LOAD_RENDER);
					if (err)
					{
						Log::PrintWarning("Could not load glyph for character code %d ('%c').", i, i);
						continue;
					}

					for (uint32_t j = 0, indexBitmap = 0, indexBuffer = 0; j < slot->bitmap.rows; ++j, indexBitmap += slot->bitmap.width, indexBuffer += m_textureWidth)
					{
						memcpy(pBuff + indexBuffer + accumulatedWidth, slot->bitmap.buffer + indexBitmap, slot->bitmap.width);
					}
					
					m_characterMap[k].first.x = (float)(accumulatedWidth) / m_textureWidth;
					m_characterMap[k].first.y = 0.f;
					accumulatedWidth += slot->bitmap.width ? slot->bitmap.width : scale;
					m_characterMap[k].second.x = (float)(accumulatedWidth) / m_textureWidth;
					m_characterMap[k].second.y = (float)slot->bitmap.rows / m_textureHeight;
				}

				// serialize image data
				RawImageData imageData;
				imageData.width = m_textureWidth;
				imageData.height = m_textureHeight;
				imageData.bitsPerPixel = 8;
				imageData.pixelFormat = RawImageData::PixelFormat::alpha;
				imageData.pixelBuffer = std::move(buff);

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
		} // namespace text
	} // namespace core
} // namespace oakvr