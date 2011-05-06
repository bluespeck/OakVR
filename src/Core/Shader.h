
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_SHADER_H__
#define __OAK3D_INCLUDE_SHADER_H__

#include "IResource.h"

namespace Oak3D
{
	namespace Core
	{

		class Shader : public IResource
		{
		public:
			

			virtual ~Shader(){}

			inline void *GetCompiledShader();
			inline ShaderType GetType();
		protected:
			void *m_pCompiledShader;
			ShaderType m_shaderType;
		};

		// --------------------------------------------------------------------------------
		inline void *Shader::GetCompiledShader()
		{
			return m_pCompiledShader;
		}

		inline ShaderType Shader::GetType()
		{
			return m_shaderType;
		}
	}	// namespace Core
}	// namespace Oak3D
#endif
