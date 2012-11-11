#pragma once

#include "Renderer/IRenderer/Shader.h"

namespace Oak3D
{
	namespace Render
	{
		class DirectX11Shader : public Shader
		{
		public:

			DirectX11Shader();
			
			inline void *GetInputLayout();
			inline void SetInputLayout( void *pInputLayout );

		protected:
			void *m_pInputLayout;
		};

		// --------------------------------------------------------------------------------
		inline void *DirectX11Shader::GetInputLayout()
		{
			return m_pInputLayout;
		}
		
		// --------------------------------------------------------------------------------
		inline void DirectX11Shader::SetInputLayout( void *pInputLayout )
		{
			m_pInputLayout = pInputLayout;
		}

	}	// namespace Render
}	// namespace Oak3D
