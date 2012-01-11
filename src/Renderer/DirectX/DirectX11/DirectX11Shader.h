
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTX11SHADER_H__
#define __OAK3D_INCLUDE_DIRECTX11SHADER_H__


#include "Renderer/IRenderer/Shader.h"

namespace Oak3D
{
	namespace Render
	{
		struct ::ID3D11InputLayout;

		class DirectX11Shader : public Shader
		{
		public:

			DirectX11Shader();
			
			inline ID3D11InputLayout *GetInputLayout();
			inline void SetInputLayout( ID3D11InputLayout *pInputLayout );

		protected:
			ID3D11InputLayout *m_pInputLayout;
		};

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

	}	// namespace Render
}	// namespace Oak3D

#endif
