#pragma once

#include "Utils/Buffer.h"
#include "Math/Vector2.h"
#include "Utils/Types.h"

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <utility>

struct FT_LibraryRec_;
struct FT_FaceRec_;

namespace oakvr
{
	namespace core
	{
		namespace text
		{
			class FontFace
			{
			public:
				FontFace(FT_LibraryRec_ *pFTLib, sp<MemoryBuffer> pFontFileBuffer, std::string fontFaceName = "");
				
				struct CharInfo
				{
					oakvr::math::Vector2 texCoords1;
					oakvr::math::Vector2 texCoords2;
					oakvr::math::Vector2 leftTopFromBaseline;
				};

				auto GetName() const -> const std::string & { return m_name; }
				auto GetMemoryBuffer() const -> const MemoryBuffer & { return m_buff; }
				auto GetCharacterMap() const -> const std::array<CharInfo, 127 - 32> & { return m_characterMap; }
				auto GetTextureWidth() const -> uint32_t { return m_textureWidth; }
				auto GetTextureHeight() const -> uint32_t { return m_textureHeight; }

				
			private:
				auto RenderGlyphs() -> MemoryBuffer;

			private:
				std::string m_name;
				MemoryBuffer m_buff;

				std::array<CharInfo, 127 - 32> m_characterMap;
				uint32_t m_textureWidth, m_textureHeight;	// pixels

				FT_FaceRec_ *m_pFTFace = nullptr;
			};
		}
	}
}