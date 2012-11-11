
#include "Renderer/DirectX/DirectX11/DirectX11Renderer.h"

namespace ro3d
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX11Renderer();
	}
} // namespace ro3d
