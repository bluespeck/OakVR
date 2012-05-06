
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDER_EFFECT_H__
#define __OAK3D_INCLUDE_RENDER_EFFECT_H__

#include "Shader.h"
#include "RendererUtils.h"

namespace Oak3D
{
	namespace Render
	{
		class Effect
		{
		public:
			Effect();
			inline void SetShader(Shader *pShader) { m_pShaders[pShader->GetType()] = pShader; }
			inline Shader *GetShader(Oak3D::Render::ShaderType shaderType) { return m_pShaders[shaderType]; }
		private:
			Shader *m_pShaders[Oak3D::Render::eST_Count];

		};
	}
}

#endif
