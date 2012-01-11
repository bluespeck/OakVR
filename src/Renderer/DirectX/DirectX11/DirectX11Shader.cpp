
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11

#include <string>
#include <cassert>

#include <d3d11.h>

#include "Renderer/IRenderer/GraphicsEngineUtils.h"

#include "DirectX11Shader.h"
#include "DirectX11GraphicsEngine.h"

#include "Oak3D/Engine.h"
#include "Core/Utils/StringID.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX11Shader::DirectX11Shader()
		: m_pInputLayout(nullptr)
		{
		}
	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_11
