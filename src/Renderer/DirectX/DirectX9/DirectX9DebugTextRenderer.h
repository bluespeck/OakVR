
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDER_DIRECTX9DEBUGTEXT_H__
#define __OAK3D_INCLUDE_RENDER_DIRECTX9DEBUGTEXT_H__

#include <string>

#include "Renderer/IRenderer/DebugTextRenderer.h"

namespace Oak3D
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
}	// namespace Oak3D

#endif
