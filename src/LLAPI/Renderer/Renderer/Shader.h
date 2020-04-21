#pragma once

#include <string>
#include <memory>

#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"


namespace oakvr::render
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

		inline auto GetType() const -> ShaderType;


		auto InvalidateContext() -> void {
											m_contextIsValid = false; }
		auto GetNativeHandle() -> void *;
	private:
		class ShaderImpl;
		std::unique_ptr<ShaderImpl> m_pImpl;

		ShaderType m_shaderType;
		bool m_contextIsValid = true;

		friend class Renderer;
	};

	// --------------------------------------------------------------------------------		
	inline auto Shader::GetType() const -> Shader::ShaderType
	{
		return m_shaderType;
	}
}


