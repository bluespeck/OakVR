
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#include "Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

#include "Oak3DInit.h"
#include "../Core/Windows/DirectX/DirectX11/DirectX11GraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Core::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Core::DirectX11GraphicsEngine();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_11