
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX9SHADER_H__
#define __OAK3D_INCLUDE_DIRECTX9SHADER_H__

#include "Renderer/IRenderer/Shader.h"

namespace Oak3D
{
	namespace Render
	{
		class DirectX9Shader : public Shader
		{
		public:

			struct DX9AdditionalInitParams : public ShaderAdditionalInitParams
			{
				uint32_t vertexFormat;
			};

			DirectX9Shader();
			virtual void Init(const Core::StringId &id, AdditionalInitParams *pAdditionalInitParams);
			
			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );

			inline void *GetInputLayout();
			inline void SetInputLayout( void *pInputLayout );
			
		protected:
			void *m_pInputLayout;
			uint32_t m_vertexFormat;

		};

		// --------------------------------------------------------------------------------
		inline uint32_t DirectX9Shader::GetVertexFormat()
		{
			return m_vertexFormat;
		}
		
		// --------------------------------------------------------------------------------
		inline void DirectX9Shader::SetVertexFormat( uint32_t vertexFormat )
		{
			m_vertexFormat = vertexFormat;
		}

		// --------------------------------------------------------------------------------
		inline void *DirectX9Shader::GetInputLayout()
		{
			return m_pInputLayout;
		}

		// --------------------------------------------------------------------------------
		inline void DirectX9Shader::SetInputLayout( void *pInputLayout )
		{
			m_pInputLayout = pInputLayout;
		}
	}	// namespace Render
}	// namespace Oak3D

#endif
