#include <fstream>
#include <cassert>
#include <cctype>

#include "Font.h"
#include "Texture.h"
#include "Oak3D/Engine.h"

namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		Font::Font()
		: m_glyphCount(0)
		, m_pGlyphData(nullptr)
		, m_pTexture(nullptr)
		{
		}

		// --------------------------------------------------------------------------------
		Font::~Font()
		{
			if(m_pTexture)
			{
				m_pTexture->Release();
				delete m_pTexture;
			}
			if(m_pGlyphData)
				delete m_pGlyphData;
		}

		// --------------------------------------------------------------------------------
		void Font::Initialize(const std::string &fontIndexFilename, const std::string &fontTextureFilename)
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

			m_pTexture = Oak3D::Engine::GetResourceManager()->GetResource<Texture>(fontTextureFilename);
		}

		// --------------------------------------------------------------------------------
		void Font::BuildVertexArray(const std::string &text, float drawX, float drawY, Font::TextVertex *&pVertices, uint32_t &numVertices)
		{						
			uint32_t numLetters = text.length();	// length of the text
			numVertices = numLetters * 6;
			float invWidth = 2.0f / Oak3D::Engine::GetRenderWindow()->GetWidth();
			float invHeight = 2.0f / Oak3D::Engine::GetRenderWindow()->GetHeight();

			drawX = drawX * invWidth - 1.f; 
			drawY = -drawY * invHeight + 1.f;
			
			pVertices = new TextVertex[numVertices];
			
			TextVertex *pVertex = pVertices;	// vertex iterator			

			// build a quad (2 triangles) for each letter
			for(uint32_t i = 0; i < numLetters; i++)
			{
				uint32_t letter = uint32_t(text[i] - 32);

				// move three pixels to the right
				if(letter == 0)
				{
					drawX = drawX + 3.0f * invWidth;
					continue;
				}
				
				// first triangle in quad.
				pVertex->position = Oak3D::Math::Vector3(drawX, drawY, 0.0f);  // Top left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3((drawX + m_pGlyphData[letter].width * invWidth), (drawY - 16 * invHeight), 0.0f);  // Bottom right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 1.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3(drawX, (drawY - 16 * invHeight), 0.0f);  // Bottom left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 1.0f);
				pVertex++;

				// second triangle in quad.
				pVertex->position = Oak3D::Math::Vector3(drawX, drawY, 0.0f);  // Top left.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].left, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3(drawX + m_pGlyphData[letter].width * invWidth, drawY, 0.0f);  // Top right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 0.0f);
				pVertex++;

				pVertex->position = Oak3D::Math::Vector3((drawX + m_pGlyphData[letter].width * invWidth), (drawY - 16 *invHeight), 0.0f);  // Bottom right.
				pVertex->texCoords = Oak3D::Math::Vector2(m_pGlyphData[letter].right, 1.0f);
				pVertex++;

				// prepare left position for next glyph
				drawX = drawX + (m_pGlyphData[letter].width + 1.0f) * invWidth;
			}
		}

	} // namespace Render
} // namespace Oak3D
