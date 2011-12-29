
#include "Core/Config/Oak3DConfig.h"

#if OAK3D_RENDERER == OAK3D_RENDERER_OPENGL

#include <string>
#include <cassert>

#include "Renderer/IRenderer/GraphicsEngineUtils.h"

#include "OpenGLShader.h"
#include "OpenGLGraphicsEngine.h"

#include "Oak3D/Engine.h"
#include "Core/Utils/StringID.h"


namespace Oak3D
{
	namespace Render
	{
		// --------------------------------------------------------------------------------
		OpenGLShader::OpenGLShader() :
		m_vertexFormat(0)
		{
		}

		// --------------------------------------------------------------------------------
		void OpenGLShader::Init(const Core::StringId &id, AditionalInitParams *pAditionalInitParams)
		{
			m_id = id;
			m_shaderType = dynamic_cast<OGLShaderAditionalInitParams*>(pAditionalInitParams)->shaderType;
			//assert((eShaderType == eST_PixelShader || vertexFormat != 0) && "Vertex shader needs vertex format when created!");
			//m_vertexFormat = vertexFormat;
		}

		// --------------------------------------------------------------------------------
		void OpenGLShader::Load()
		{
			m_state = eRS_Loading;
			OpenGLGraphicsEngine *pGE = (OpenGLGraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->CreateShader(this);
			m_state = eRS_Ready;
		}

		// --------------------------------------------------------------------------------
		void OpenGLShader::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void OpenGLShader::Release()
		{
			OpenGLGraphicsEngine *pGE = (OpenGLGraphicsEngine*)Engine::GetInstance()->GetGraphicsEngine();
			pGE->ReleaseShader(this);

		}
	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_DIRECTX_9