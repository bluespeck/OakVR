
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
		class ID3D11InputLayout;

		class DirectX11Shader : public Shader
		{
		public:
			DirectX11Shader();
			void Init(const std::wstring &path, ShaderType eShaderType, uint32_t vertexFormat = 0);
			
			// overrides
			virtual void Load();
			virtual void Reload();
			virtual void Release();

		private:
			virtual void Init( const std::wstring &path );

		protected:
			ID3D11InputLayout *m_pInputLayout;
			uint32_t m_vertexFormat;

		};

	}	// namespace Core
}	// namespace Oak3D
#endif
