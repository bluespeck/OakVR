#include "Common.h"
#include "Renderer/Renderer/ShaderProgram.h"
#include "Renderer/Renderer/Shader.h"
#include "Utils/Types.h"
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
			, sp<oakvr::core::MemoryBuffer> vsBuffer
			, sp<oakvr::core::MemoryBuffer> psBuffer
			, sp<oakvr::core::MemoryBuffer> gsBuffer
			, sp<oakvr::core::MemoryBuffer> dsBuffer
			, sp<oakvr::core::MemoryBuffer> hsBuffer)
			: m_pImpl { std::make_unique<ShaderProgramImpl>() }
		{
			PROFILER_FUNC_SCOPED_TIMER;
			
			// Create OpenGL shader program
			m_pImpl->m_shaderProgramId = glCallAndCheck(glCreateProgram);
			m_contextIsValid = true;

			if (vsBuffer.get())
			{
				m_vs = std::make_unique<Shader>(Shader::ShaderType::vertex, *vsBuffer);
				glCallAndCheck(glAttachShader,m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_vs->GetNativeHandle()));
			}
			else
				Log::Warning("File buffer for %s vertex shader is empty!", shaderProgram.c_str());

			if (psBuffer.get())
			{
				m_ps = std::make_unique<Shader>(Shader::ShaderType::pixel, *psBuffer);
				glCallAndCheck(glAttachShader, m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_ps->GetNativeHandle()));
			}
			else
				Log::Warning("File buffer for %s pixel shader is empty!", shaderProgram.c_str());

			if (gsBuffer.get())
			{
				m_gs = std::make_unique<Shader>(Shader::ShaderType::geometry, *gsBuffer);
				glCallAndCheck(glAttachShader, m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_gs->GetNativeHandle()));
			}
			else
				Log::Warning("File buffer for %s geometry shader is empty!", shaderProgram.c_str());

			if (dsBuffer.get())
			{
				m_ds = std::make_unique<Shader>(Shader::ShaderType::domain, *dsBuffer);
				glCallAndCheck(glAttachShader, m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_ds->GetNativeHandle()));
			}
			else
				Log::Warning("File buffer for %s domain shader is empty!", shaderProgram.c_str());

			if (hsBuffer.get())
			{
				m_hs = std::make_unique<Shader>(Shader::ShaderType::hull, *hsBuffer);
				glCallAndCheck(glAttachShader, m_pImpl->m_shaderProgramId, reinterpret_cast<GLuint>(m_hs->GetNativeHandle()));
			}
			else
				Log::Warning("File buffer for %s hull shader is empty!", shaderProgram.c_str());

			glCallAndCheck(glLinkProgram, m_pImpl->m_shaderProgramId);
		}

		ShaderProgram::~ShaderProgram()
		{
			if (m_contextIsValid)
			{
				glUseProgram(0);
				glDeleteProgram(m_pImpl->m_shaderProgramId);
			}
			else
			{
				if (m_vs)
					m_vs->InvalidateContext();
				if(m_ps)
					m_ps->InvalidateContext();
				if(m_gs)
					m_gs->InvalidateContext();
				if (m_ds)
					m_ds->InvalidateContext();
				if (m_hs)
					m_hs->InvalidateContext();
			}
		}

		void *ShaderProgram::GetNativeHandle()
		{
			return reinterpret_cast<void *>(m_pImpl->m_shaderProgramId);
		}
	}
}