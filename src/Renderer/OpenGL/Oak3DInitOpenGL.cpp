
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#include "Core/Config/OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

#include "Core/Config/Oak3DInit.h"
#include "Renderer/OpenGL/OpenGLGraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Render::OpenGLGraphicsEngine();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_OPENGL