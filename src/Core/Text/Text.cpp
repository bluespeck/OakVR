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
#include <cmath>

namespace oakvr::core
{
	// --------------------------------------------------------------------------------
	Text::Text()
		: m_pFTLib{ nullptr }
	{
		FT_Error err = FT_Init_FreeType(&m_pFTLib);
		if (err)
			Log::Error("Could not initialize OakVR text manager.");
	}

	// --------------------------------------------------------------------------------
	Text::~Text()
	{

	}

	// --------------------------------------------------------------------------------
	auto Text::AddFontFace(sp<MemoryBuffer> fontFileBuff) -> void
	{
		m_fontFaces.emplace_back(m_pFTLib, fontFileBuff);	// add new text::FontFace object to m_fontFaces
		auto face = m_fontFaces.back();
		auto buff = face.GetMemoryBuffer();
		m_pRM->CreateResourceFromMemory(face.GetName() + "_texture", buff);
	}

	// --------------------------------------------------------------------------------
	auto Text::RenderText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName, float scale /* = 1.0f */, float angle /*= 0.f*/) const -> void
	{
		float scaleFactor = 0.05f;

		auto it = FindFontFace(fontName);

		if (it != m_fontFaces.end())
		{
			std::vector<oakvr::render::VertexElementDescriptor> ved{
				oakvr::render::VertexElementDescriptor::Semantic::position,
				oakvr::render::VertexElementDescriptor::Semantic::tex_coord,
				oakvr::render::VertexElementDescriptor::Semantic::color
			};

			int vertexStride = ComputeVertexStride(ved);
			oakvr::core::MemoryBuffer vb{ text.length() * 4 * vertexStride };
			oakvr::core::MemoryBuffer ib{ text.length() * 6 * sizeof(uint32_t) };


			auto cm = it->GetCharacterMap();

			float posX = 0.0f;
			float posY = 0.0f;

			// create the mesh for this text
			int vertexStrideInFloats = vertexStride / sizeof(float);
			std::unique_ptr<float[]> pVertices = std::make_unique<float[]>(text.length() * 4 * vertexStrideInFloats);
			std::unique_ptr<uint32_t[]> pIndices = std::make_unique<uint32_t[]>(text.length() * 6);
			for (int i = 0; i < text.length(); ++i)
			{
				if (text[i] < ' ')
				{
					oakvr::Log::Warning("Trying to output a character that is not in the range 32-127! [%c]", text[i]);
					continue;
				}

				const auto &charProps = cm[text[i] - ' '];

				float horizontalNormalizationFactor = 1.f / it->GetTextureWidth();
				float verticalNormalizationFactor = 1.f / it->GetTextureHeight();
				float cwPixels = fabs(charProps.texCoords2.x - charProps.texCoords1.x) * scaleFactor;
				float chPixels = fabs(charProps.texCoords2.y - charProps.texCoords1.y) * scaleFactor;
				float clPixels = charProps.leftTopFromBaseline.x * scaleFactor;
				float ctPixels = charProps.leftTopFromBaseline.y * scaleFactor;

				// Vertex # layout
				//	position.x
				//	position.y
				//	position.z
				//	texcoord.u
				//	texcoord.v
				//	color.r
				//	color.g
				//	color.b

				int offset = i * 4 * vertexStrideInFloats;

				// Vertex #1
				pVertices[offset + 0 * vertexStrideInFloats + 0] = posX + clPixels;
				pVertices[offset + 0 * vertexStrideInFloats + 1] = posY - chPixels + ctPixels;
				pVertices[offset + 0 * vertexStrideInFloats + 2] = 0.0f;
				pVertices[offset + 0 * vertexStrideInFloats + 3] = charProps.texCoords1.x * horizontalNormalizationFactor;
				pVertices[offset + 0 * vertexStrideInFloats + 4] = charProps.texCoords2.y * verticalNormalizationFactor;
				pVertices[offset + 0 * vertexStrideInFloats + 5] = color.r;
				pVertices[offset + 0 * vertexStrideInFloats + 6] = color.g;
				pVertices[offset + 0 * vertexStrideInFloats + 7] = color.b;
				pVertices[offset + 0 * vertexStrideInFloats + 8] = color.a;

				// Vertex #2
				pVertices[offset + 1 * vertexStrideInFloats + 0] = posX + cwPixels + clPixels;
				pVertices[offset + 1 * vertexStrideInFloats + 1] = posY - chPixels + ctPixels;
				pVertices[offset + 1 * vertexStrideInFloats + 2] = 0.0f;
				pVertices[offset + 1 * vertexStrideInFloats + 3] = charProps.texCoords2.x * horizontalNormalizationFactor;
				pVertices[offset + 1 * vertexStrideInFloats + 4] = charProps.texCoords2.y * verticalNormalizationFactor;
				pVertices[offset + 1 * vertexStrideInFloats + 5] = color.r;
				pVertices[offset + 1 * vertexStrideInFloats + 6] = color.g;
				pVertices[offset + 1 * vertexStrideInFloats + 7] = color.b;
				pVertices[offset + 1 * vertexStrideInFloats + 8] = color.a;

				// Vertex #3
				pVertices[offset + 2 * vertexStrideInFloats + 0] = posX + cwPixels + clPixels;
				pVertices[offset + 2 * vertexStrideInFloats + 1] = posY + ctPixels;
				pVertices[offset + 2 * vertexStrideInFloats + 2] = 0.0f;
				pVertices[offset + 2 * vertexStrideInFloats + 3] = charProps.texCoords2.x * horizontalNormalizationFactor;
				pVertices[offset + 2 * vertexStrideInFloats + 4] = charProps.texCoords1.y * verticalNormalizationFactor;
				pVertices[offset + 2 * vertexStrideInFloats + 5] = color.r;
				pVertices[offset + 2 * vertexStrideInFloats + 6] = color.g;
				pVertices[offset + 2 * vertexStrideInFloats + 7] = color.b;
				pVertices[offset + 2 * vertexStrideInFloats + 8] = color.a;

				// Vertex #4
				pVertices[offset + 3 * vertexStrideInFloats + 0] = posX + clPixels;
				pVertices[offset + 3 * vertexStrideInFloats + 1] = posY + ctPixels;
				pVertices[offset + 3 * vertexStrideInFloats + 2] = 0.0f;
				pVertices[offset + 3 * vertexStrideInFloats + 3] = charProps.texCoords1.x * horizontalNormalizationFactor;
				pVertices[offset + 3 * vertexStrideInFloats + 4] = charProps.texCoords1.y * verticalNormalizationFactor;
				pVertices[offset + 3 * vertexStrideInFloats + 5] = color.r;
				pVertices[offset + 3 * vertexStrideInFloats + 6] = color.g;
				pVertices[offset + 3 * vertexStrideInFloats + 7] = color.b;
				pVertices[offset + 3 * vertexStrideInFloats + 8] = color.a;

				offset = i * 6;
				// Index #1
				pIndices[offset + 0] = i * 4;
				pIndices[offset + 1] = i * 4 + 1;
				pIndices[offset + 2] = i * 4 + 2;
				pIndices[offset + 3] = i * 4;
				pIndices[offset + 4] = i * 4 + 2;
				pIndices[offset + 5] = i * 4 + 3;

				posX += 1.1f * cwPixels;	// advance horrizontally (small hack to limit glyphs from overlapping)
			}

			memcpy(vb.GetDataPtr(), pVertices.get(), vb.Size());
			memcpy(ib.GetDataPtr(), pIndices.get(), ib.Size());

			std::vector<StringId> vecTextures = { it->GetName() + "_texture" };
			auto pMaterial = std::make_shared<oakvr::render::Material>("DefaultText");

			auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(ved, vb, static_cast<uint8_t>(sizeof(uint32_t)), ib, pMaterial, vecTextures);

			auto pMesh = std::make_shared<oakvr::render::Mesh>();
			pMesh->AddMeshElement(pMeshElem);
			pMesh->SetWorldMatrix(oakvr::math::Matrix44::Translation(position) * oakvr::math::Matrix44::RotationZ(angle) * oakvr::math::Matrix44::Scale(scale));
			m_pRenderer->RegisterOneFrameMesh(pMesh);
			m_pRenderer->RegisterShaderProgram("DefaultText");

		}
		else
		{
			Log::Warning("Could not find font face \"%s\" for rendering.", fontName.c_str());
		}
	}

	auto Text::GetGlyphWidth(char character, std::string fontName, float scale) -> float
	{
		auto it = FindFontFace(fontName);

		if (it != m_fontFaces.end())
		{
			auto cm = it->GetCharacterMap();
			if (character < ' ')
				return -1;

			auto charProps = cm[character];
			return 1.1f * fabs(charProps.texCoords2.x - charProps.texCoords1.x) * 0.05f * scale; //(1.1 hack from renderText and 0.05 scalefactor from renderText)
		}

		return 0.0f;
	}

	auto Text::GetGlyphHeight(char character, std::string fontName, float scale) -> float
	{
		auto it = FindFontFace(fontName);

		if (it != m_fontFaces.end())
		{
			auto cm = it->GetCharacterMap();
			if (character < ' ')
				return -1;

			auto charProps = cm[character];
			return 1.1f * fabs(charProps.texCoords2.y - charProps.texCoords1.y) * 0.05f * scale; //(1.1 hack from renderText and 0.05 scalefactor from renderText)
		}
		return 0.0f;
	}

	// --------------------------------------------------------------------------------
	auto Text::FindFontFace(const std::string &name) const -> std::vector<text::FontFace>::const_iterator
	{
		return std::find_if(m_fontFaces.begin(), m_fontFaces.end(), [&](const text::FontFace &face)
		{
			return name == std::string(face.GetName());
		});
	}

	// --------------------------------------------------------------------------------
	auto Text::FindFontFace(const std::string &name) -> std::vector<text::FontFace>::iterator
	{
		return std::find_if(m_fontFaces.begin(), m_fontFaces.end(), [&](const text::FontFace &face)
		{
			return name == std::string(face.GetName());
		});
	}
}
