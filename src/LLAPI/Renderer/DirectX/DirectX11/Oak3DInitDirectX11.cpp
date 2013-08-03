
#include "Renderer/DirectX/DirectX11/DirectX11Renderer.h"

namespace oakvr
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX11Renderer();
	}
} // namespace oakvr
