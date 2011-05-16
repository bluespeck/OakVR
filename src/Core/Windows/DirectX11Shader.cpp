
#include <string>
#include <assert.h>

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
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Init(const std::wstring &path, ShaderType eShaderType)
		{
			m_shaderType = eShaderType;
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
			m_pCompiledShader = pGE->CreateShaderFromFile(m_id.GetStrId(), m_shaderType);
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void DirectX11Shader::Release()
		{
			DirectX11GraphicsEngine *pGE = (DirectX11GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->ReleaseShader(m_pCompiledShader, m_shaderType);
			
		}
	}	// namespace Core
}	// namespace Oak3D
