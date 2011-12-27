
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OPENGLDEBUGTEXT_H__
#define __OAK3D_INCLUDE_OPENGLDEBUGTEXT_H__

#include <string>

#include "Renderer/IRenderer/DebugText.h"

namespace Oak3D
{
	namespace Render
	{
		class Font;
		class Shader;

		class OpenGLDebugText : public DebugText
		{
		public:
			OpenGLDebugText();
			~OpenGLDebugText();

			// overrides
			virtual void Init();
			virtual void OutputText( const std::string &text, uint32_t x, uint32_t y );
			
		protected:
			Font *m_pFont;
			Shader *m_pVertexShader;
			Shader *m_pFragmentShader;
		};
	}	// namespace Render
}	// namespace Oak3D

#endif
