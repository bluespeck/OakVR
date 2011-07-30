
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#include "OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include "Oak3DInit.h"
#include "../Core/Windows/DirectX/DirectX9/DirectX9GraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Core::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Core::DirectX9GraphicsEngine();
	}
}

#endif // OAK3D_RENDERER_DIRECTX_9