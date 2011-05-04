
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_SHADER_H__
#define __OAK3D_INCLUDE_SHADER_H__

#include "IResource.h"

namespace Oak3D
{
	namespace Core
	{

		class Shader : public IResource
		{
		public:
			inline void *GetCompiledShader();
		protected:
			void *m_pCompiledShader;
		};

		// --------------------------------------------------------------------------------
		inline void *Shader::GetCompiledShader()
		{
			return m_pCompiledShader;
		}

	}	// namespace Core
}	// namespace Oak3D
#endif