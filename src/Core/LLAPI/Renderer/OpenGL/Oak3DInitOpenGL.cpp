
#include "Renderer/OpenGL/OpenGLRenderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::OpenGLRenderer();
	}
} // namespace Oak3D

