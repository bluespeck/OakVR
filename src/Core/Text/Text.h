#pragma once

#include "Oakvr/Interface.h"
#include "Utils/Singleton.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"
#include "FontFace.h"
#include "Math/Vector3.h"
#include "Renderer/Renderer/Color.h"


#include <vector>
#include <memory>

// preventing the pull of the entiry freetype header
struct FT_LibraryRec_;

namespace oakvr
{
	namespace render
	{
		class Renderer;
	}
	namespace core
	{
		class ResourceManager;
	}

	namespace core
	{
		class Text : public Singleton < Text >
		{
			friend class Singleton < Text > ;
		public:
			auto AddFontFace(sp<oakvr::core::MemoryBuffer> fontFileBuff) -> void;
			
			auto RenderText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName, float scale = 1.0f, float angle = 0.0f) const -> void;

			auto GetGlyphWidth(char character, std::string fontName, float scale = 1.0f) -> float;
			auto GetGlyphHeight(char character, std::string fontName, float scale = 1.0f) -> float;

			auto SetResourceManagerPtr(std::shared_ptr<oakvr::core::ResourceManager> pRM) -> void { m_pRM = pRM; }
			auto SetRendererPtr(std::shared_ptr<oakvr::render::Renderer> pRenderer) -> void { m_pRenderer = pRenderer; }
			
		private:
			Text();
			~Text();

			

			auto FindFontFace(const std::string &name) const -> std::vector<text::FontFace>::const_iterator;
			auto FindFontFace(const std::string &name) -> std::vector<text::FontFace>::iterator;
		private:
			FT_LibraryRec_ *m_pFTLib;
			std::vector<text::FontFace> m_fontFaces;

			std::shared_ptr<oakvr::core::ResourceManager> m_pRM;
			std::shared_ptr<oakvr::render::Renderer> m_pRenderer;
		};
	}

	namespace core
	{
		inline auto AddFontFace(std::string fileName)  -> void{ oakvr::core::Text::GetInstance().AddFontFace(oakvr::core::GetResource(fileName)); }
	}
	namespace render
	{
		inline auto DrawText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName, float scale = 1.0f, float angle = 0.0f) -> void{ oakvr::core::Text::GetInstance().RenderText(text, position, color, fontName, scale, angle); }
		inline auto GetGlyphWidth(char glyph, std::string fontName, float scale = 1.0f) -> float { 
			return oakvr::core::Text::GetInstance().GetGlyphWidth(glyph, fontName, scale); }
		inline auto GetGlyphHeight(char glyph, std::string fontName, float scale = 1.0f) -> float{ 
			return oakvr::core::Text::GetInstance().GetGlyphHeight(glyph, fontName, scale); }
	}
}