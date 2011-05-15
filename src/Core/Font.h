// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_FONT_H__
#define __OAK3D_INCLUDE_FONT_H__

#include <cstdint>
#include <string>

#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace Oak3D
{
	namespace Core
	{
		class Texture;

		class Font
		{
		public:
			struct GlyphProperties
			{
				uint32_t asciiCode;
				float left, right;
				uint32_t width;
			};

			struct TextVertex
			{
				Oak3D::Math::Vector3 position;
				Oak3D::Math::Vector2 texCoords;
			};

			Font();
			~Font();

			void Initialize(const std::wstring &fontIndexFilename, const std::wstring &fontTextureFilename);

			// builds a triangle list containing the text mesh for the given coordinates
			TextVertex *BuildVertexArray(const std::wstring &text, float drawX, float drawY);
		protected:
			Texture *m_pTexture;
			GlyphProperties *m_pGlyphData;
			uint32_t m_glyphCount;
		};
	} // namespace Core
} // namespace Oak3D


#endif
