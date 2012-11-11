
#include "Renderer/DirectX/DirectX11/DirectX11Renderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX11Renderer();
	}
} // namespace Oak3D
