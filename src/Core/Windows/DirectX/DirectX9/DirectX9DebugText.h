
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX9DEBUGTEXT_H__
#define __OAK3D_INCLUDE_DIRECTX9DEBUGTEXT_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "../../../DebugText.h"

namespace Oak3D
{
	namespace Core
	{

		class DirectX9DebugText : public DebugText
		{
		public:
			DirectX9DebugText();
			~DirectX9DebugText();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::wstring &text, uint32_t x, uint32_t y );
			
		protected:
			//class Font *m_pFont;
			struct ID3DXFont *m_pFont;
			//class DirectX9Shader *m_pVertexShader;
			//class DirectX9Shader *m_pPixelShader;
			
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
