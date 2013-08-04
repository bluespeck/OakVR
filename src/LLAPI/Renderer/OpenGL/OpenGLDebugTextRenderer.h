
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAKVR_INCLUDE_RENDER_OPENGLDEBUGTEXT_H__
#define __OAKVR_INCLUDE_RENDER_OPENGLDEBUGTEXT_H__

#include <string>

#include "Renderer/Renderer/DebugTextRenderer.h"

namespace oakvr
{
	namespace render
	{
		class Font;
		class Shader;

		class OpenGLDebugTextRenderer : public DebugTextRenderer
		{
		public:
			OpenGLDebugTextRenderer();
			~OpenGLDebugTextRenderer();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			Font *m_pFont;
			Shader *m_pVertexShader;
			Shader *m_pFragmentShader;
		};
	}	// namespace Render
}	// namespace oakvr

#endif
