#pragma once

#include <string>

#include "Renderer/Renderer/DebugTextRenderer.h"

namespace oakvr
{
	namespace render
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
	}	// namespace render
}	// namespace oakvr
