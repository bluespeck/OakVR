
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

#include "Core/Config/Oak3DInit.h"
#include "Renderer/DirectX/DirectX11/DirectX11Renderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX11Renderer();
	}
} // namespace Oak3D

#endif // OAK3D_RENDERER_DIRECTX_11