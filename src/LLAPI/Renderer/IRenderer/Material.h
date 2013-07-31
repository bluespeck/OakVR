#pragma once

#include <string>
#include "Math/Vector3.h"
#include "Color.h"

namespace oakvr
{
	namespace Render
	{

		class Material
		{
		public:
			std::wstring m_name;

			oakvr::Render::Color m_vAmbient;
			oakvr::Render::Color m_vDiffuse;
			oakvr::Render::Color m_vSpecular;

			int m_nShininess;
			float m_fAlpha;

			bool m_bSpecular;

		public:
			Material();
			~Material(void);
		};
	} // namespace Render
} // namespace oakvr
