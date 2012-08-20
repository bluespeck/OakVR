
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#include "Core/Config/OAk3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include "Core/Config/Oak3DInit.h"
#include "Renderer/DirectX/DirectX9/DirectX9Renderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX9Renderer();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_9
