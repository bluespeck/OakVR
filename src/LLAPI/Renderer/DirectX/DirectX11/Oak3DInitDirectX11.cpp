
#include "Renderer/DirectX/DirectX11/DirectX11Renderer.h"

namespace oakvr
{
	// --------------------------------------------------------------------------------
	render::Renderer *CreateRenderer()
	{
		return new render::DirectX11Renderer();
	}
} // namespace oakvr
