
#include "Renderer/OpenGL/OpenGLRenderer.h"

namespace ro3d
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::OpenGLRenderer();
	}
} // namespace ro3d

