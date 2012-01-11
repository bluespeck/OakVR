#include "Shader.h"
#include "Oak3D/Engine.h"
#include "GraphicsEngine.h"



namespace Oak3D
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
			GraphicsEngine *pGE = (GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
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
			GraphicsEngine *pGE = (GraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->ReleaseShader(this);
			m_state = eRS_Released;
		}
	}
}
