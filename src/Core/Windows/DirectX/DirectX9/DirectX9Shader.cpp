
#include "../../../Oak3DCoreConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9

#include <string>
#include <cassert>

#include <d3d9.h>

#include "../../../GraphicsEngineUtils.h"

#include "DirectX9Shader.h"
#include "DirectX9GraphicsEngine.h"

#include "../../../Engine.h"
#include "../../../../Utils/StringID.h"


namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		DirectX9Shader::DirectX9Shader() :
		m_vertexFormat(0)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Init(const std::wstring &path, ShaderType eShaderType, uint32_t vertexFormat)
		{
			m_shaderType = eShaderType;
			assert((eShaderType == eST_PixelShader || vertexFormat != 0) && "Vertex shader needs vertex format when created!");
			m_vertexFormat = vertexFormat;
			Init(path);
		}

		// --------------------------------------------------------------------------------
		void DirectX9Shader::Init( const std::wstring &path )
		{
			m_id = Utils::StringId(path);

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
	}	// namespace Core
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_9
