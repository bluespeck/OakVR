
#include "Renderer/OpenGL/OpenGLRenderer.h"

namespace oakvr
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::OpenGLRenderer();
	}
} // namespace oakvr

