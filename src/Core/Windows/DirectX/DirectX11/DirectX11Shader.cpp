
#include <string>
#include <cassert>

#include <d3d11.h>

#include "../GraphicsEngineUtils.h"

#include "DirectX11Shader.h"
#include "DirectX11GraphicsEngine.h"

#include "../Engine.h"
#include "../../Utils/StringID.h"


namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		DirectX11Shader::DirectX11Shader()
		: m_pInputLayout(nullptr)
		, m_vertexFormat(0)
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Init(const std::wstring &path, ShaderType eShaderType, uint32_t vertexFormat)
		{
			m_shaderType = eShaderType;
			assert((eShaderType == eST_PixelShader || vertexFormat != 0) && "Vertex shader needs vertex format when created!");
			m_vertexFormat = vertexFormat;
			Init(path);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Init( const std::wstring &path )
		{
			m_id = Utils::StringId(path);

		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Load()
		{
			
			DirectX11GraphicsEngine *pGE = (DirectX11GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->CreateShader(this);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Release()
		{
			DirectX11GraphicsEngine *pGE = (DirectX11GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->ReleaseShader(this);
			
		}
	}	// namespace Core
}	// namespace Oak3D
