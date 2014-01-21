#include "Common.h"
#include "Renderer/Renderer/Shader.h"
#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RendererUtils.h"
#include "Log/Log.h"




//#include "oakvr/Engine.h"
//#include "Core/Utils/StringId.h"

#include <string>
#include <cassert>

namespace oakvr
{
	namespace render
	{
		class Shader::ShaderImpl
		{
		public:
			GLuint shaderId;
		};

		// --------------------------------------------------------------------------------
		Shader::Shader(ShaderType shaderType, const oakvr::core::MemoryBuffer &buff)
			: m_pImpl{ new Shader::ShaderImpl}
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
			GLuint shaderId = glCreateShader(st);
			m_pImpl->shaderId = shaderId;
			
			const char *shaderSource = reinterpret_cast<const char *>(buff.GetDataPtr());
			GLint length = buff.Size();

			glShaderSource(shaderId, 1, &shaderSource, &length);
			glCompileShader(shaderId);
			
			GLint compileSuccessfull;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccessfull);
			if (compileSuccessfull == GL_FALSE)
			{
				GLcharARB infoLog[1024];
				GLsizei charsWritten;
				glGetInfoLogARB(shaderId, 1024, &charsWritten, infoLog);
				infoLog[charsWritten] = 0;
				Log::PrintWarning("OpenGL shader compilation has failed: %s\n", infoLog);
			}
		}

		Shader::~Shader()
		{

		}

		void Shader::Use()
		{
			static GLint shader_id = glCreateProgram();
			static bool bFirstTime = true;
			if (bFirstTime)
			{
				GLenum err = 0;
				glAttachShader(shader_id, m_pImpl->shaderId); // Attach a vertex shader to the program
				//glAttachShader(shader_id, shader_fp); // Attach the fragment shader to the program

				glBindAttribLocation(shader_id, 0, "in_Position"); // Bind a constant attribute location for positions of vertices
				err = glGetError();
				if (err)
					oakvr::Log::PrintError("Err Use %x", err);

				glLinkProgram(shader_id); // Link the vertex and fragment shaders in the program
				err = glGetError();
				if (err)
					oakvr::Log::PrintError("Err Use2 %x", err);
				
				//validateProgram(shader_id); // Validate the shader program
				glUseProgram(shader_id);
				err = glGetError();
				if (err)
					oakvr::Log::PrintError("Err Use3 %x", err);
			}
			bFirstTime = false;
		}
	}	// namespace render
}	// namespace oakvr
