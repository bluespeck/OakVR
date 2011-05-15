#include <fstream>
#include <cassert>
#include <cctype>

#include "Font.h"
#include "Texture.h"

namespace Oak3D
{
	namespace Core
	{
		void Font::Initialize(const std::wstring &fontIndexFilename, const std::wstring &fontTextureFilename)
		{
			std::ifstream indexFile(fontIndexFilename);
			
			if(indexFile.fail())
			{
				assert(0 && "Could not read the specified font index file!");
				return;
			}

			// Read glyph count
			indexFile >> m_glyphCount;
			m_pGlyphData = new GlyphProperties[m_glyphCount];
						
			// skip white spaces until first font glyph
			while(std::isspace(indexFile.peek()))
			{				
				indexFile.ignore();
			} 
			
			// Read ASCII characters
			for(uint32_t i = 0; i < m_glyphCount; i++)
			{
				indexFile >> m_pGlyphData[i].asciiCode;
				indexFile.ignore(2);	// skip ASCII code char
				indexFile >> m_pGlyphData[i].left;
				indexFile >> m_pGlyphData[i].right;
				indexFile >> m_pGlyphData[i].width;
			}
			indexFile.close();

			m_pTexture->Init(fontTextureFilename);
			m_pTexture->Load();
		}

		Font::TextVertex *Font::BuildVertexArray(const std::wstring &text, float drawX, float drawY)
		{
			TextVertex* pVertices;
			
			uint32_t numLetters = text.length();	// length of the text

			pVertices = new TextVertex[numLetters * 6];
			
			TextVertex *pVertex = pVertices;	// vertex iterator			

			// build a quad (2 triangles) for each letter
			for(uint32_t i = 0; i < numLetters; i++)
			{
				uint32_t letter = uint32_t(text[i] - 32);

				// move three pixels to the right
				if(letter == 0)
				{
					drawX = drawX + 3.0f;
					continue;
				}
				// first triangle in quad.
				pVertex->position = Oak3D::Math::Vector3(drawX, drawY, 0.0f);  // Top left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3((drawX + m_pGlyphData[letter].width), (drawY - 16), 0.0f);  // Bottom right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 1.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3(drawX, (drawY - 16), 0.0f);  // Bottom left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 1.0f);
				pVertex++;

				// second triangle in quad.
				pVertex->position = Oak3D::Math::Vector3(drawX, drawY, 0.0f);  // Top left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3(drawX + m_pGlyphData[letter].width, drawY, 0.0f);  // Top right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3((drawX + m_pGlyphData[letter].width), (drawY - 16), 0.0f);  // Bottom right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 1.0f);
				pVertex++;

				// prepare left position for next glyph
				drawX = drawX + m_pGlyphData[letter].width + 1.0f;
			}

			return pVertices;
		}

	} // namespace Core
} // namespace Oak3D