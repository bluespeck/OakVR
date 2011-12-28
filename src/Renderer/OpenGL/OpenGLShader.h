
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OPENGLSHADER_H__
#define __OAK3D_INCLUDE_OPENGLSHADER_H__

#include "Renderer/IRenderer/Shader.h"

namespace Oak3D
{
	namespace Render
	{
		class OpenGLShader : public Shader
		{
		public:			
			struct OGLShaderAditionalInitParams : public AditionalInitParams
			{

			};

			typedef OGLShaderAditionalInitParams AIP; 

			OpenGLShader();
			void Init( const Core::StringId &id, AditionalInitParams *pInitParams = nullptr); //ShaderType eShaderType, uint32_t vertexFormat = 0 );

			// overrides
			virtual void Load();
			virtual void Reload();
			virtual void Release();

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );

			virtual void Init( const Core::StringId &id );

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

	}	// namespace Render
}	// namespace Oak3D

#endif
