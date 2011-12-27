
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#include "Core/Config/OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include "Core/Config/Oak3DInit.h"
#include "Renderer/DirectX/DirectX9/DirectX9GraphicsEngine.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Render::DirectX9GraphicsEngine();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_9
