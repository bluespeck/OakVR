#pragma once

#include <string>

#include "Renderer/IRenderer/DebugTextRenderer.h"

namespace oakvr
{
	namespace Render
	{

		class DirectX9DebugTextRenderer : public DebugTextRenderer
		{
		public:
			DirectX9DebugTextRenderer();
			~DirectX9DebugTextRenderer();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			struct ID3DXFont *m_pFont;
			
		};
	}	// namespace Render
}	// namespace oakvr
