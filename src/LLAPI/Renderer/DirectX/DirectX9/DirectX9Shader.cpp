
#include <string>
#include <cassert>

#include <d3d9.h>

#include "Renderer/IRenderer/RendererUtils.h"

#include "DirectX9Shader.h"
#include "DirectX9Renderer.h"

#include "Utils/StringId.h"


namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX9Shader::DirectX9Shader() :
		m_vertexFormat(0)
		{
		}

	}	// namespace Render
}	// namespace ro3d
