#pragma once


#include "RendererUtils.h"

namespace oakvr
{
	namespace render
	{
		class Shader
		{
		public:
			
			Shader() : m_pCompiledShader(nullptr), m_shaderType(eST_VertexShader) {}
			virtual ~Shader() {}

			inline void *GetCompiledShader();
			inline ShaderType GetType();
			inline void SetCompiledShader( void *pCompiledShader );
		protected:
			void *m_pCompiledShader;
			ShaderType m_shaderType;
		};

		// --------------------------------------------------------------------------------
		inline void *Shader::GetCompiledShader()
		{
			return m_pCompiledShader;
		}

		// --------------------------------------------------------------------------------		
		inline void Shader::SetCompiledShader(void *pCompiledShader)
		{
			m_pCompiledShader = pCompiledShader;
		}

		// --------------------------------------------------------------------------------		
		inline ShaderType Shader::GetType()
		{
			return m_shaderType;
		}
	}	// namespace render
}	// namespace oakvr


