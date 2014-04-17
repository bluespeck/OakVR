#pragma once

#include "Utils/Buffer.h"
#include "Math/Vector2.h"

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
				FontFace(FT_LibraryRec_ *pFTLib, std::shared_ptr<MemoryBuffer> pFontFileBuffer, std::string fontFaceName = "");
				
				const std::string &GetName() const { return m_name; }
				const MemoryBuffer &GetMemoryBuffer() const { return m_buff; }
				const std::array<std::pair<oakvr::math::Vector2, oakvr::math::Vector2>, 127 - 32> &GetCharacterMap() const { return m_characterMap; }
				uint32_t GetTextureWidth() const { return m_textureWidth; }
				uint32_t GetTextureHeight() const { return m_textureHeight; }
			private:
				MemoryBuffer RenderGlyphs();

			private:
				std::string m_name;
				MemoryBuffer m_buff;
				std::array<std::pair<oakvr::math::Vector2, oakvr::math::Vector2>, 127 - 32> m_characterMap;
				uint32_t m_textureWidth, m_textureHeight;	// pixels

				FT_FaceRec_ *m_pFTFace = nullptr;
			};
		}
	}
}