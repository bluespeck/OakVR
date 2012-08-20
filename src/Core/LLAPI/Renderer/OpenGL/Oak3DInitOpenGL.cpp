
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#include "Core/Config/OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

#include "Core/Config/Oak3DInit.h"
#include "Renderer/OpenGL/OpenGLRenderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::OpenGLRenderer();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_OPENGL