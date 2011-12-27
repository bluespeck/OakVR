
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX11DEBUGTEXT_H__
#define __OAK3D_INCLUDE_DIRECTX11DEBUGTEXT_H__

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <string>

#include "Renderer/IRenderer/DebugText.h"

namespace Oak3D
{
	namespace Render
	{

		class DirectX11DebugText : public DebugText
		{
		public:
			DirectX11DebugText();
			~DirectX11DebugText();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			class Font *m_pFont;
			class DirectX11Shader *m_pVertexShader;
			class DirectX11Shader *m_pPixelShader;
			
		};
	}	// namespace Render
}	// namespace Oak3D

#endif
