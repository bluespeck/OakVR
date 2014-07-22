#pragma once

#include "Shader.h"
#include "Utils/Buffer.h"

#include <memory>
#include <string>

namespace oakvr
{
	namespace render
	{
		class ShaderProgram
		{
		public:
			ShaderProgram::ShaderProgram(const std::string &shaderProgram
				, std::shared_ptr<oakvr::core::MemoryBuffer> vsBuffer
				, std::shared_ptr<oakvr::core::MemoryBuffer> psBuffer
				, std::shared_ptr<oakvr::core::MemoryBuffer> gsBuffer
				, std::shared_ptr<oakvr::core::MemoryBuffer> dsBuffer
				, std::shared_ptr<oakvr::core::MemoryBuffer> hsBuffer);
			~ShaderProgram();


			void *GetNativeHandle();
		private:

			std::unique_ptr<Shader> m_vs, m_ps, m_gs, m_ds, m_hs;

			class ShaderProgramImpl;
			std::unique_ptr<ShaderProgramImpl> m_pImpl;
		};
	}
}