
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MATERIAL_H__
#define __OAK3D_INCLUDE_MATERIAL_H__

#include <string>
#include "Core/ResourceManager/IResource.h"
#include "Core/Math/Vector3.h"
#include "Renderer/IRenderer/Color.h"

namespace Oak3D
{
	namespace Render
	{

		class Material : public Oak3D::Core::IResource
		{
		public:
			std::wstring m_name;

			Oak3D::Render::Color m_vAmbient;
			Oak3D::Render::Color m_vDiffuse;
			Oak3D::Render::Color m_vSpecular;

			int m_nShininess;
			float m_fAlpha;

			bool m_bSpecular;

		public:
			Material();
			~Material(void);
		};
	} // namespace Render
} // namespace Oak3D

#endif
