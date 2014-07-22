#pragma once

#include "Oakvr/Interface.h"
#include "Utils/Singleton.h"
#include "Utils/Buffer.h"
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
			void AddFontFace(std::shared_ptr<oakvr::core::MemoryBuffer> fontFileBuff);
			
			void RenderText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName, float scale = 1.0f) const;

			void SetResourceManagerPtr(std::shared_ptr<oakvr::core::ResourceManager> pRM) { m_pRM = pRM; }
			void SetRendererPtr(std::shared_ptr<oakvr::render::Renderer> pRenderer) { m_pRenderer = pRenderer; }
			
		private:
			Text();
			~Text();

			

			std::vector<text::FontFace>::const_iterator FindFontFace(const std::string &name) const;
			std::vector<text::FontFace>::iterator FindFontFace(const std::string &name);
		private:
			FT_LibraryRec_ *m_pFTLib;
			std::vector<text::FontFace> m_fontFaces;

			std::shared_ptr<oakvr::core::ResourceManager> m_pRM;
			std::shared_ptr<oakvr::render::Renderer> m_pRenderer;
		};
	}

	namespace core
	{
		inline void AddFontFace(std::string fileName) { oakvr::core::Text::GetInstance().AddFontFace(oakvr::core::GetResource(fileName)); }
	}
	namespace render
	{
		inline void DrawText(std::string text, oakvr::math::Vector3 position, oakvr::render::Color color, std::string fontName, float scale = 1.0f) { oakvr::core::Text::GetInstance().RenderText(text, position, color, fontName, scale); }
	}
}