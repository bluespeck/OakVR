

#include "Renderer/DirectX/DirectX9/DirectX9Renderer.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::IRenderer *CreateRenderer()
	{
		return new Render::DirectX9Renderer();
	}
} // namespace Oak3D