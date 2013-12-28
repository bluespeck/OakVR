#pragma once

#include <cstdint>

#include "Renderer/Renderer/Shader.h"

namespace oakvr
{
	namespace render
	{
		class OpenGLShader : public Shader
		{
		public:			

			OpenGLShader();

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );

		protected:
			uint32_t m_vertexFormat;

		};

		// --------------------------------------------------------------------------------
		inline uint32_t OpenGLShader::GetVertexFormat()
		{
			return m_vertexFormat;
		}

		// --------------------------------------------------------------------------------
		inline void OpenGLShader::SetVertexFormat( uint32_t vertexFormat )
		{
			m_vertexFormat = vertexFormat;
		}

	}	// namespace render
}	// namespace oakvr
