
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#include "OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

#include "Oak3DInit.h"
#include "../Core/Windows/OpenGL/OpenGLGraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Core::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Core::OpenGLGraphicsEngine();
	}
}

#endif // OAK3D_RENDERER_OPENGL