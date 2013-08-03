

#include "Renderer/DirectX/DirectX9/DirectX9Renderer.h"

namespace oakvr
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX9Renderer();
	}
} // namespace oakvr