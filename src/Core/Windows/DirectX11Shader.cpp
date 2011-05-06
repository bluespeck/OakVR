
#include <string>
#include <assert.h>
#include "../GraphicsEngineUtils.h"

#include "DirectX11Shader.h"
#include "DirectX11GraphicsEngine.h"

#include "../Engine.h"
#include "../../Utils/StringID.h"


namespace Oak3D
{
	namespace Core
	{
		void DirectX11Shader::Init(const std::wstring &path, ShaderType eShaderType)
		{
			m_shaderType = eShaderType;
			Init(path);
		}

		void DirectX11Shader::Init( const std::wstring &path )
		{
			m_id = Utils::StringID(path);

		}

		void DirectX11Shader::Load()
		{
			
			DirectX11GraphicsEngine *pGE = (DirectX11GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->CreateShaderFromFile(m_id.GetStrID(), m_shaderType);
			// Compile shader from file
			ID3D10Blob *pShader;
			ID3D10Blob *pErrorMsg;
			switch(m_shaderType)
			{
			case eST_VertexShader:
				{
					HR(D3DX11CompileFromFileW(m_id.GetStrID().c_str(), nullptr, nullptr, "VertexShader", "vs_5_0", 0, 0, nullptr, &pShader, &pErrorMsg, nullptr));
					break;
				}
			case eST_PixelShader:
				{
					HR(D3DX11CompileFromFileW(m_id.GetStrID().c_str(), nullptr, nullptr, "PixelShader", "ps_5_0", 0, 0, nullptr, &pShader, &pErrorMsg, nullptr));
					break;
				}
			default:
				assert("Shader was not correctly initialized!" && 0);
				return;
			}

			// Create DirectX shader
			


		}

		void DirectX11Shader::Reload()
		{
		}

		void DirectX11Shader::Release()
		{
		}
	}	// namespace Core
}	// namespace Oak3D
