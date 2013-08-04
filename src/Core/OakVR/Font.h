#pragma once

#include <cstdint>
#include <string>

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace oakvr
{
	namespace render
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
				oakvr::Math::Vector3 position;
				oakvr::Math::Vector2 texCoords;
			};

			Font();
			~Font();

			void Initialize(const std::string &fontIndexFilename, const std::string &fontTextureFilename);

			// builds a triangle list containing the text mesh for the given coordinates
			void BuildVertexArray(const std::string &text, float drawX, float drawY, TextVertex *&pVertices, uint32_t &numVertices);
			inline Texture *GetTexture();
		protected:
			Texture *m_pTexture;
			GlyphProperties *m_pGlyphData;
			uint32_t m_glyphCount;
		};

		// --------------------------------------------------------------------------------
		inline Texture *Font::GetTexture()
		{
			return m_pTexture;
		}
	} // namespace Render
} // namespace oakvr

