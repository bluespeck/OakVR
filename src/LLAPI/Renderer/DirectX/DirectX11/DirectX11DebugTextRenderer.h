#pragma once

#include <string>

#include "Renderer/IRenderer/DebugTextRenderer.h"

namespace oakvr
{
	namespace Render
	{

		class DirectX11DebugTextRenderer : public DebugTextRenderer
		{
		public:
			DirectX11DebugTextRenderer();
			~DirectX11DebugTextRenderer();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			class Font *m_pFont;
			class DirectX11Shader *m_pVertexShader;
			class DirectX11Shader *m_pPixelShader;
			
		};
	}	// namespace Render
}	// namespace oakvr
