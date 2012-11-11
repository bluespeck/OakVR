#pragma once

#include <string>
#include "Math/Vector3.h"
#include "Color.h"

namespace ro3d
{
	namespace Render
	{

		class Material
		{
		public:
			std::wstring m_name;

			ro3d::Render::Color m_vAmbient;
			ro3d::Render::Color m_vDiffuse;
			ro3d::Render::Color m_vSpecular;

			int m_nShininess;
			float m_fAlpha;

			bool m_bSpecular;

		public:
			Material();
			~Material(void);
		};
	} // namespace Render
} // namespace ro3d
