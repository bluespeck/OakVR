#include "Common.h"
#include "Renderer/Renderer/Shader.h"
#include "Renderer/Renderer/Renderer.h"
#include "Utils/RenderUtils.h"
#include "Log/Log.h"




//#include "oakvr/Engine.h"
//#include "Core/Utils/StringId.h"

#include <string>
#include <cassert>

namespace oakvr::render
{
	class Shader::ShaderImpl
	{
	public:
		GLuint shaderId;
	};

	// --------------------------------------------------------------------------------
	Shader::Shader(ShaderType shaderType, const oakvr::core::MemoryBuffer& buff)
		: m_pImpl{ new Shader::ShaderImpl }
	{
		GLenum st = GL_VERTEX_SHADER;
		switch (shaderType)
		{
		case ShaderType::vertex:
			st = GL_VERTEX_SHADER;
			break;
		case ShaderType::pixel:
			st = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::geometry:
			st = GL_GEOMETRY_SHADER;
			break;
		case ShaderType::hull:
			st = GL_TESS_CONTROL_SHADER;
			break;
		case ShaderType::domain:
			st = GL_TESS_EVALUATION_SHADER;
			break;
		default:
			break;
		}
		GLuint shaderId = glCallAndCheck(glCreateShader, st);
		m_pImpl->shaderId = shaderId;

		const char* shaderSource = reinterpret_cast<const char*>(buff.GetDataPtr());
		GLint length = static_cast<GLint>(buff.Size());

		glCallAndCheck(glShaderSource, shaderId, 1, &shaderSource, &length);
		glCallAndCheck(glCompileShader, shaderId);

		GLint compileSuccessfull;
		glCallAndCheck(glGetShaderiv, shaderId, GL_COMPILE_STATUS, &compileSuccessfull);
		if (compileSuccessfull == GL_FALSE)
		{
			GLcharARB infoLog[1024];
			GLsizei charsWritten;
			glCallAndCheck(glGetInfoLogARB, shaderId, 1024, &charsWritten, infoLog);
			infoLog[charsWritten] = 0;
			Log::Warning("OpenGL shader compilation has failed: %s", infoLog);
		}
	}

	Shader::~Shader()
	{
		if (m_contextIsValid == true)
			glCallAndCheck(glDeleteShader, m_pImpl->shaderId);
	}

	auto Shader::GetNativeHandle() -> void*
	{
		return reinterpret_cast<void*>(m_pImpl->shaderId);
	}
}