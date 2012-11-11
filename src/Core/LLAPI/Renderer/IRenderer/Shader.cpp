/*
#include "Shader.h"
#include "ro3d/Engine.h"
#include "IRenderer.h"



namespace ro3d
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		void Shader::Init(const Core::StringId &id, AdditionalInitParams *pAdditionalInitParams)
		{
			m_id = id;
			m_shaderType = dynamic_cast<ShaderAdditionalInitParams*>(pAdditionalInitParams)->shaderType;
		}

		// --------------------------------------------------------------------------------
		void Shader::Load()
		{
			m_state = eRS_Loading;
			IRenderer *pGE = (IRenderer*)Engine::GetInstance()->GetRenderer();
			pGE->CreateShader(this);
			m_state = eRS_Ready;
		}

		// --------------------------------------------------------------------------------
		void Shader::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void Shader::Release()
		{
			IRenderer *pGE = (IRenderer*)Engine::GetInstance()->GetRenderer();
			pGE->ReleaseShader(this);
			m_state = eRS_Released;
		}
	}
}

*/
