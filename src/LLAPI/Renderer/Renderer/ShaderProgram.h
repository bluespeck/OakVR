#pragma once

#include "Shader.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"

#include <memory>
#include <string>

namespace oakvr
{
	namespace render
	{
		class ShaderProgram
		{
		public:
			ShaderProgram(const std::string &shaderProgram
				, sp<oakvr::core::MemoryBuffer> vsBuffer
				, sp<oakvr::core::MemoryBuffer> psBuffer
				, sp<oakvr::core::MemoryBuffer> gsBuffer
				, sp<oakvr::core::MemoryBuffer> dsBuffer
				, sp<oakvr::core::MemoryBuffer> hsBuffer);
			~ShaderProgram();


			void *GetNativeHandle();
			auto InvalidateContext()  -> void{ m_contextIsValid = false; }
		private:

			std::unique_ptr<Shader> m_vs, m_ps, m_gs, m_ds, m_hs;

			class ShaderProgramImpl;
			std::unique_ptr<ShaderProgramImpl> m_pImpl;

			bool m_contextIsValid = false;
		};
	}
}