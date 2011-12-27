
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX9DEBUGTEXT_H__
#define __OAK3D_INCLUDE_DIRECTX9DEBUGTEXT_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "Renderer/IRenderer/DebugText.h"

namespace Oak3D
{
	namespace Render
	{

		class DirectX9DebugText : public DebugText
		{
		public:
			DirectX9DebugText();
			~DirectX9DebugText();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			struct ID3DXFont *m_pFont;
			
		};
	}	// namespace Render
}	// namespace Oak3D

#endif
