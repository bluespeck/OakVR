/*
#include "Shader.h"
#include "oakvr/Engine.h"
#include "Renderer.h"



namespace oakvr
{
	namespace render
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
			Renderer *pGE = (Renderer*)Engine::GetInstance()->GetRenderer();
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
			Renderer *pGE = (Renderer*)Engine::GetInstance()->GetRenderer();
			pGE->ReleaseShader(this);
			m_state = eRS_Released;
		}
	}
}

*/
