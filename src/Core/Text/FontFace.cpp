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
				FT_Error err = FT_New_Memory_Face(pFTLib, pFontFileBuffer->GetDataPtr(), static_cast<FT_Long>(pFontFileBuffer->Size()), 0, &fontFace);
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
				int scale = 20;
				FT_Set_Char_Size(m_pFTFace, scale * 64, 0, 300, 0);

				// upper left corner of the texture?
				int penX = 0;
				int32_t maxRows = 0;
				int32_t maxSlotAdvanceX = 0;
				for (char i = 33, k = 0; i < 127; ++i, ++k)
				{
					FT_Error err = FT_Load_Char(m_pFTFace, i, FT_LOAD_RENDER);
					if (err)
					{
						Log::PrintWarning("Could not load glyph for character code %d ('%c').", i, i);
						continue;
					}
					
					if (maxRows < slot->bitmap.rows)
						maxRows = slot->bitmap.rows;
					int32_t advanceX = slot->advance.x >> 6; // 1/64s of a pixel
					if (maxSlotAdvanceX < advanceX)
						maxSlotAdvanceX = advanceX;
					penX += advanceX + 2; 
				}
				penX += maxSlotAdvanceX / 2; // add width of space
				m_textureWidth = oakvr::math::NextPowerOfTwo(penX);
				m_textureHeight = oakvr::math::NextPowerOfTwo(maxRows);

				MemoryBuffer buff(m_textureWidth * m_textureHeight * sizeof(uint8_t)); // uint8_t corresponding to GRAYS
				MemoryBuffer::value_type *pBuff = buff.GetDataPtr();
				memset(pBuff, 0, buff.Size());


				int32_t accumulatedWidth = 0;

				// add space
				m_characterMap[0].texCoords1.x = 0.f;
				m_characterMap[0].texCoords1.y = 0.f;
				accumulatedWidth += maxSlotAdvanceX / 2;
				m_characterMap[0].texCoords2.x = static_cast<float>(accumulatedWidth);
				m_characterMap[0].texCoords2.y = static_cast<float>(maxRows);
				m_characterMap[0].leftTopFromBaseline.x = 0.;
				m_characterMap[0].leftTopFromBaseline.y = static_cast<float>(maxRows);

				for (char i = 33, k = 1; i < 127; ++i, ++k)
				{
					FT_Error err = FT_Load_Char(m_pFTFace, i, FT_LOAD_RENDER);
					if (err)
					{
						Log::PrintWarning("Could not load glyph for character code %d ('%c').", i, i);
						continue;
					}
					int32_t slotAdvanceX = slot->advance.x >> 6;

					for (int32_t j = 0, indexBitmap = 0, indexBuffer =  0; j < slot->bitmap.rows; ++j, indexBitmap += slot->bitmap.width, indexBuffer += m_textureWidth)
					{
						memcpy(pBuff + indexBuffer + accumulatedWidth, slot->bitmap.buffer + indexBitmap, slot->bitmap.width);
					}
					
					m_characterMap[k].texCoords1.x = static_cast<float>(accumulatedWidth);
					m_characterMap[k].texCoords1.y = static_cast<float>(0.f);
					accumulatedWidth += slotAdvanceX;
					m_characterMap[k].texCoords2.x = static_cast<float>(accumulatedWidth);
					m_characterMap[k].texCoords2.y = static_cast<float>(slot->bitmap.rows);
					m_characterMap[k].leftTopFromBaseline.x = static_cast<float>(slot->bitmap_left);
					m_characterMap[k].leftTopFromBaseline.y = static_cast<float>(slot->bitmap_top);
					accumulatedWidth += 2;
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

				BufferWriter<MemoryBuffer::value_type> bufferWriter(rawImageData);
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