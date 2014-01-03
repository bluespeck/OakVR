#pragma once

#include <memory>

#include "RendererUtils.h"

namespace oakvr
{
	namespace render
	{
		class Shader
		{
		public:
			
			Shader();
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


