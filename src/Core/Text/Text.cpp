#include "Text.h"
#include "Log/Log.h"
#include "ResourceManager/ResourceManager.h"
#include "Renderer/Renderer/Renderer.h"

#include "Math/Vector3.h"
#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/Material.h"

#include "Utils/BufferReader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <cstdint>
#include <memory>

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		Text::Text()
			: m_pFTLib{ nullptr }
		{
			FT_Error err = FT_Init_FreeType(&m_pFTLib);
			if (err)
				Log::PrintError("Could not initialize OakVR text manager.");
		}

		// --------------------------------------------------------------------------------
		Text::~Text()
		{
			
		}

		// --------------------------------------------------------------------------------
		void Text::AddFontFace(std::shared_ptr<MemoryBuffer> fontFileBuff)
		{
			m_fontFaces.emplace_back(m_pFTLib, fontFileBuff);	// add new text::FontFace object to m_fontFaces
			auto face = m_fontFaces.back();
			auto buff = face.GetMemoryBuffer();
			m_pRM->CreateResourceFromMemory(face.GetName() + "_texture", buff);
		}

		// --------------------------------------------------------------------------------
		void Text::RenderText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName) const
		{
			auto it = FindFontFace(fontName);

			if (it != m_fontFaces.end())
			{
				auto pMesh = std::make_shared<oakvr::render::Mesh>();

				std::vector<oakvr::render::VertexElementDescriptor> ved{
						{ 12, oakvr::render::VertexElementDescriptor::Semantic::position },
						{ 8, oakvr::render::VertexElementDescriptor::Semantic::tex_coord },
						{ 12, oakvr::render::VertexElementDescriptor::Semantic::color }
				};

				oakvr::core::MemoryBuffer vb{ text.length() * 4 * ComputeVertexStride(ved) * sizeof(float) };
				oakvr::core::MemoryBuffer ib{ text.length() * 6 * sizeof(uint32_t) };


				auto cm = it->GetCharacterMap();

				float posX = 0.0f;
				float posY = 0.0f;
				// create the mesh for this text
				std::unique_ptr<float[]> pVertices = std::make_unique<float[]>(text.length() * 4 * ComputeVertexStride(ved) * sizeof(float));
				std::unique_ptr<uint32_t[]> pIndices = std::make_unique<uint32_t[]>(text.length() * 6 * sizeof(uint32_t));
				for (int i = 0; i < text.length(); ++i)
				{
					if (text[i] < ' ' || text[i] > 127)
					{
						oakvr::Log::PrintWarning("Trying to output a character that is not in the range 32-127! [%c]", text[i]);
						continue;
					}
					const auto &charProps = cm[text[i] - ' '];
					float charWidth = charProps.second.x - charProps.first.x;
					float charHeight = charProps.second.y - charProps.first.y;
					float cwPixels = charWidth * it->GetTextureWidth()/4.f;
					float chPixels = charHeight * it->GetTextureHeight()/4.f;
					// Vertex #1
					pVertices[i * 4 * 8 + 0 * 8 + 0] = position.x + posX;				// x
					pVertices[i * 4 * 8 + 0 * 8 + 1] = position.y + posY;				// y
					pVertices[i * 4 * 8 + 0 * 8 + 2] = position.z + 0.0f;				// z
					pVertices[i * 4 * 8 + 0 * 8 + 3] = charProps.first.x;				// u
					pVertices[i * 4 * 8 + 0 * 8 + 4] = charProps.second.y;				// v
					pVertices[i * 4 * 8 + 0 * 8 + 5] = color.r;
					pVertices[i * 4 * 8 + 0 * 8 + 6] = color.g;
					pVertices[i * 4 * 8 + 0 * 8 + 7] = color.b;

					// Vertex #2
					pVertices[i * 4 * 8 + 1 * 8 + 0] = position.x + posX + cwPixels;	// x
					pVertices[i * 4 * 8 + 1 * 8 + 1] = position.y + posY;				// y
					pVertices[i * 4 * 8 + 1 * 8 + 2] = position.z + 0.0f;				// z
					pVertices[i * 4 * 8 + 1 * 8 + 3] = charProps.second.x;				// u
					pVertices[i * 4 * 8 + 1 * 8 + 4] = charProps.second.y;				// v
					pVertices[i * 4 * 8 + 1 * 8 + 5] = color.r;
					pVertices[i * 4 * 8 + 1 * 8 + 6] = color.g;
					pVertices[i * 4 * 8 + 1 * 8 + 7] = color.b;

					// Vertex #3
					pVertices[i * 4 * 8 + 2 * 8 + 0] = position.x + posX + cwPixels;			// x
					pVertices[i * 4 * 8 + 2 * 8 + 1] = position.y + posY + chPixels;			// y
					pVertices[i * 4 * 8 + 2 * 8 + 2] = position.z + 0.0f;						// z
					pVertices[i * 4 * 8 + 2 * 8 + 3] = charProps.second.x;				// u
					pVertices[i * 4 * 8 + 2 * 8 + 4] = charProps.first.y;				// v
					pVertices[i * 4 * 8 + 2 * 8 + 5] = color.r;
					pVertices[i * 4 * 8 + 2 * 8 + 6] = color.g;
					pVertices[i * 4 * 8 + 2 * 8 + 7] = color.b;

					// Vertex #4
					pVertices[i * 4 * 8 + 3 * 8 + 0] = position.x + posX;					// x
					pVertices[i * 4 * 8 + 3 * 8 + 1] = position.y + posY + chPixels;		// y
					pVertices[i * 4 * 8 + 3 * 8 + 2] = position.z + 0.0f;					// z
					pVertices[i * 4 * 8 + 3 * 8 + 3] = charProps.first.x;				// u
					pVertices[i * 4 * 8 + 3 * 8 + 4] = charProps.first.y;				// v
					pVertices[i * 4 * 8 + 3 * 8 + 5] = color.r;
					pVertices[i * 4 * 8 + 3 * 8 + 6] = color.g;
					pVertices[i * 4 * 8 + 3 * 8 + 7] = color.b;

					
					// Index #1
					pIndices[i * 6 + 0] = i * 4 ;
					pIndices[i * 6 + 1] = i * 4 + 1;
					pIndices[i * 6 + 2] = i * 4 + 2;
					pIndices[i * 6 + 3] = i * 4 ;
					pIndices[i * 6 + 4] = i * 4 + 2;
					pIndices[i * 6 + 5] = i * 4 + 3;

					posX += cwPixels;	// advance horrizontally
				}
				
				memcpy(vb.GetDataPtr(), pVertices.get(), vb.Size());
				memcpy(ib.GetDataPtr(), pIndices.get(), ib.Size());

				std::vector<std::string> vecTextures = { it->GetName() + "_texture" };
				auto pMaterial = std::make_shared<oakvr::render::Material>(std::string("DefaultText"));

				auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(ved, vb, sizeof(uint32_t), ib, pMaterial, vecTextures);

				pMesh->AddMeshElement(pMeshElem);
				m_pRenderer->RegisterOneFrameMesh(pMesh);
				m_pRenderer->RegisterShaderProgram("DefaultText");

			}
			else
			{
				Log::PrintWarning("Could not find font face \"%s\" for rendering.", fontName.c_str());
			}
		}

		// --------------------------------------------------------------------------------
		std::vector<text::FontFace>::const_iterator Text::FindFontFace(const std::string &name) const
		{
			return std::find_if(m_fontFaces.begin(), m_fontFaces.end(), [&](const text::FontFace &face)
			{
				return name == std::string(face.GetName());
			});
		}

		// --------------------------------------------------------------------------------
		std::vector<text::FontFace>::iterator Text::FindFontFace(const std::string &name)
		{
			return std::find_if(m_fontFaces.begin(), m_fontFaces.end(), [&](const text::FontFace &face)
			{
				return name == std::string(face.GetName());
			});
		}
	}
}
