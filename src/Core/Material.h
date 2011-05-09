
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MATERIAL_H__
#define __OAK3D_INCLUDE_MATERIAL_H__

#include <string>
#include "IResource.h"
#include "../Math/Vector3.h"
#include "../Utils/Color.h"

namespace Oak3D
{
	namespace Core
	{

		class Material : public IResource
		{
		public:
			std::wstring m_name;

			Oak3D::Utils::Color m_vAmbient;
			Oak3D::Utils::Color m_vDiffuse;
			Oak3D::Utils::Color m_vSpecular;

			int m_nShininess;
			float m_fAlpha;

			bool m_bSpecular;

		public:
			Material();
			~Material(void);
		};
	} // namespace Core
}

#endif
