
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include <string>
#include <cassert>

#include <d3d9.h>

#include "Renderer/IRenderer/GraphicsEngineUtils.h"

#include "DirectX9Shader.h"
#include "DirectX9GraphicsEngine.h"

#include "Oak3D/Engine.h"
#include "Core/Utils/StringID.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		DirectX9Shader::DirectX9Shader() :
		m_vertexFormat(0)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Init(const std::string &path, ShaderType eShaderType, uint32_t vertexFormat)
		{
			m_shaderType = eShaderType;
			assert((eShaderType == eST_PixelShader || vertexFormat != 0) && "Vertex shader needs vertex format when created!");
			m_vertexFormat = vertexFormat;
			Init(path);
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Init( const std::string &path )
		{
			m_id = Core::StringId(path);

		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Load()
		{
			
			DirectX9GraphicsEngine *pGE = (DirectX9GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->CreateShader(this);
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Release()
		{
			DirectX9GraphicsEngine *pGE = (DirectX9GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->ReleaseShader(this);
			
		}
	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_9
