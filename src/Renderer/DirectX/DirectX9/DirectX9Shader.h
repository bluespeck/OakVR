
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX9SHADER_H__
#define __OAK3D_INCLUDE_DIRECTX9SHADER_H__

#include "Renderer/IRenderer/Shader.h"

namespace Oak3D
{
	namespace Render
	{
		struct ::IDirect3DVertexDeclaration9;

		class DirectX9Shader : public Shader
		{
		public:
			DirectX9Shader();
			void Init( const std::string &path, ShaderType eShaderType, uint32_t vertexFormat = 0 );
			
			// overrides
			virtual void Load();
			virtual void Reload();
			virtual void Release();

			inline uint32_t GetVertexFormat();
			inline void SetVertexFormat( uint32_t vertexFormat );

			inline IDirect3DVertexDeclaration9 *GetInputLayout();
			inline void SetInputLayout( IDirect3DVertexDeclaration9 *pInputLayout );
			
		private:
			virtual void Init( const std::string &path );

		protected:
			IDirect3DVertexDeclaration9 *m_pInputLayout;
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
		inline IDirect3DVertexDeclaration9 *DirectX9Shader::GetInputLayout()
		{
			return m_pInputLayout;
		}

		// --------------------------------------------------------------------------------
		inline void DirectX9Shader::SetInputLayout( IDirect3DVertexDeclaration9 *pInputLayout )
		{
			m_pInputLayout = pInputLayout;
		}
	}	// namespace Render
}	// namespace Oak3D

#endif
