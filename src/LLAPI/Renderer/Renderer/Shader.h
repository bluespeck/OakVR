#pragma once

#include <string>
#include <memory>

#include "RendererUtils.h"
#include "Utils/Buffer.h"


namespace oakvr
{
	namespace render
	{
		class Shader
		{
		public:
			enum class ShaderType
			{
				vertex,
				pixel,
				geometry,
				hull,
				domain,
			};

			Shader(ShaderType shaderType, const oakvr::core::MemoryBuffer &buff);
			~Shader();
			inline ShaderType GetType();
			
		protected:
			class ShaderImpl;
			std::unique_ptr<ShaderImpl> m_pImpl;
			ShaderType m_shaderType;
		};

		// --------------------------------------------------------------------------------		
		inline Shader::ShaderType Shader::GetType()
		{
			return m_shaderType;
		}
	}	// namespace render
}	// namespace oakvr


