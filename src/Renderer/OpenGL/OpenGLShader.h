
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
			struct OGLShaderAdditionalInitParams : public AdditionalInitParams
			{	
			};

			OpenGLShader();
			void Init( const Core::StringId &id, AdditionalInitParams *pAdditionalInitParams);

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

	}	// namespace Render
}	// namespace Oak3D

#endif
