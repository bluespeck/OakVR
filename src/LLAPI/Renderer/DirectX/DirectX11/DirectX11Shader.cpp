
#include <string>
#include <cassert>

#include <d3d11.h>

#include "Renderer/Renderer/RendererUtils.h"

#include "DirectX11Shader.h"
#include "DirectX11Renderer.h"

#include "Utils/StringId.h"


namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		DirectX11Shader::DirectX11Shader()
		: m_pInputLayout(nullptr)
		{
		}
	}	// namespace render
}	// namespace oakvr
