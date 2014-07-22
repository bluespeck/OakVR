#include "Common.h"
#include "Renderer/Renderer/ShaderProgram.h"
#include "Renderer/Renderer/Shader.h"
#include "Log/Log.h"
#include "Profiler/Profiler.h"


#include <memory>
#include <string>

namespace oakvr
{
	namespace render
	{
		class ShaderProgram::ShaderProgramImpl
		{
		public:
			GLuint m_shaderProgramId;
		};

		ShaderProgram::ShaderProgram(const std::string &shaderProgram
			, std::shared_ptr<oakvr::core::MemoryBuffer> vsBuffer
			, std::shared_ptr<oakvr::core::MemoryBuffer> psBuffer
			, std::shared_ptr<oakvr::core::MemoryBuffer> gsBuffer
			, std::shared_ptr<oakvr::core::MemoryBuffer> dsBuffer
			, std::shared_ptr<oakvr::core::MemoryBuffer> hsBuffer)
			: m_pImpl { std::make_unique<ShaderProgramImpl>() }
		{
			PROFILER_FUNC_SCOPED_TIMER;
			
			// Create OpenGL shader program
			m_pImpl->m_shaderProgramId = glCreateProgram();

			if (vsBuffer.get())
			{
				m_vs = std::make_unique<Shader>(Shader::ShaderType::vertex, *vsBuffer);
				glAttachShader(m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_vs->GetNativeHandle()));
			}
			else
				Log::PrintWarning("File buffer for %s vertex shader is empty!", shaderProgram.c_str());

			if (psBuffer.get())
			{
				m_ps = std::make_unique<Shader>(Shader::ShaderType::pixel, *psBuffer);
				glAttachShader(m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_ps->GetNativeHandle()));
			}
			else
				Log::PrintWarning("File buffer for %s pixel shader is empty!", shaderProgram.c_str());

			if (gsBuffer.get())
			{
				m_gs = std::make_unique<Shader>(Shader::ShaderType::geometry, *gsBuffer);
				glAttachShader(m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_gs->GetNativeHandle()));
			}
			else
				Log::PrintWarning("File buffer for %s geometry shader is empty!", shaderProgram.c_str());

			if (dsBuffer.get())
			{
				m_ds = std::make_unique<Shader>(Shader::ShaderType::domain, *dsBuffer);
				glAttachShader(m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_ds->GetNativeHandle()));
			}
			else
				Log::PrintWarning("File buffer for %s domain shader is empty!", shaderProgram.c_str());

			if (hsBuffer.get())
			{
				m_hs = std::make_unique<Shader>(Shader::ShaderType::hull, *hsBuffer);
				glAttachShader(m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_hs->GetNativeHandle()));
			}
			else
				Log::PrintWarning("File buffer for %s hull shader is empty!", shaderProgram.c_str());

			glLinkProgram(m_pImpl->m_shaderProgramId);
		}

		ShaderProgram::~ShaderProgram()
		{
			glUseProgram(0);
			glDeleteProgram(m_pImpl->m_shaderProgramId);
		}

		void *ShaderProgram::GetNativeHandle()
		{
			return reinterpret_cast<void *>(m_pImpl->m_shaderProgramId);
		}
	}
}