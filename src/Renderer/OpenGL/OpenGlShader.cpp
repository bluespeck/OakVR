
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
	}	// namespace Render
}	// namespace Oak3D

#endif // OAK3D_OPENGL
