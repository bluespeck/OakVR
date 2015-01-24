#pragma once

#include <string>
#include <memory>

#include "Utils/RenderUtils.h"
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


			void InvalidateContext() { m_contextIsValid = false; }
			void *GetNativeHandle();
		private:
			class ShaderImpl;
			std::unique_ptr<ShaderImpl> m_pImpl;
			ShaderType m_shaderType;
			bool m_contextIsValid = true;

			friend class Renderer;
		};

		// --------------------------------------------------------------------------------		
		inline Shader::ShaderType Shader::GetType()
		{
			return m_shaderType;
		}
	}	// namespace render
}	// namespace oakvr


