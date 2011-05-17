
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX11SHADER_H__
#define __OAK3D_INCLUDE_DIRECTX11SHADER_H__

#include "../Shader.h"

namespace Oak3D
{
	namespace Core
	{
		struct ::ID3D11InputLayout;

		class DirectX11Shader : public Shader
		{
		public:
			DirectX11Shader();
			void Init( const std::wstring &path, ShaderType eShaderType, uint32_t vertexFormat = 0 );
			
			// overrides
			virtual void Load();
			virtual void Reload();
			virtual void Release();

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );
			
			inline ID3D11InputLayout *GetInputLayout();
			inline void SetInputLayout( ID3D11InputLayout *pInputLayout );


		private:
			virtual void Init( const std::wstring &path );

		protected:
			ID3D11InputLayout *m_pInputLayout;
			uint32_t m_vertexFormat;

		};

		// --------------------------------------------------------------------------------
		inline uint32_t DirectX11Shader::GetVertexFormat()
		{
			return m_vertexFormat;
		}
		
		// --------------------------------------------------------------------------------
		inline void DirectX11Shader::SetVertexFormat( uint32_t vertexFormat )
		{
			m_vertexFormat = vertexFormat;
		}

		// --------------------------------------------------------------------------------
		inline ID3D11InputLayout *DirectX11Shader::GetInputLayout()
		{
			return m_pInputLayout;
		}
		
		// --------------------------------------------------------------------------------
		inline void DirectX11Shader::SetInputLayout( ID3D11InputLayout *pInputLayout )
		{
			m_pInputLayout = pInputLayout;
		}


	}	// namespace Core
}	// namespace Oak3D
#endif
