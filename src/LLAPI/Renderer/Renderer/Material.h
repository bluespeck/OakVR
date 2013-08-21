#pragma once

#include <string>
#include "Color.h"

namespace oakvr
{
	namespace render
	{

		class Material
		{
		public:
			std::string m_name;

			oakvr::render::Color m_vAmbient;
			oakvr::render::Color m_vDiffuse;
			oakvr::render::Color m_vSpecular;

			int m_nShininess;
			float m_fAlpha;

			bool m_bSpecular;
			std::string m_shaderName;

		public:
			Material();
			~Material(void);
		};
	} // namespace Render
} // namespace oakvr
