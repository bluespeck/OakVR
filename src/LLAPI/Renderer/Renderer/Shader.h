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
			
			Shader(const std::string &resourceName, const Buffer<uint8_t> &buff);
			inline ShaderType GetType();
			
		protected:
			class ShaderImpl;
			std::unique_ptr<ShaderImpl> *m_pImpl;
			ShaderType m_shaderType;
		};

		// --------------------------------------------------------------------------------		
		inline ShaderType Shader::GetType()
		{
			return m_shaderType;
		}
	}	// namespace render
}	// namespace oakvr


