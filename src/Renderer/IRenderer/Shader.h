
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_SHADER_H__
#define __OAK3D_INCLUDE_SHADER_H__

#include "Core/ResourceManager/IResource.h"
#include "GraphicsEngineUtils.h"

namespace Oak3D
{
	namespace Render
	{
		class Shader : public Core::IResource
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
	}	// namespace Render
}	// namespace Oak3D

#endif
