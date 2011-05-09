
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

		class DirectX11Shader : public Shader
		{
		public:		
			void Init(const std::wstring &path, ShaderType eShaderType);
			
			// overrides
			virtual void Load();
			virtual void Reload();
			virtual void Release();

		private:
			virtual void Init( const std::wstring &path );
		};

	}	// namespace Core
}	// namespace Oak3D
#endif
