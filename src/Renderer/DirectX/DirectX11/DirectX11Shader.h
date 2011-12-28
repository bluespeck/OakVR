
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

			struct DX11AditionalInitParams : AditionalInitParams
			{
				ShaderType shaderType;
			};

			DirectX11Shader();
			// overrides
			virtual void Init( const Core::StringId &id, AditionalInitParams *pAditionalInitParams = nullptr);
			virtual void Load();
			virtual void Reload();
			virtual void Release();
			
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
