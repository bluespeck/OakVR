
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

#include "Core/Config/Oak3DInit.h"
#include "Renderer/DirectX/DirectX11/DirectX11GraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Render::DirectX11GraphicsEngine();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_11