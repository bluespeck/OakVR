#pragma once

#include <string>
#include "Math/Vector3.h"
#include "Color.h"

namespace Oak3D
{
	namespace Render
	{

		class Material
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
