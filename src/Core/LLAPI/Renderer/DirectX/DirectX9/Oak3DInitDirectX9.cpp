

#include "Renderer/DirectX/DirectX9/DirectX9Renderer.h"

namespace ro3d
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX9Renderer();
	}
} // namespace ro3d