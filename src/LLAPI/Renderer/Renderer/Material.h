#pragma once

#include <string>
#include "Color.h"

namespace oakvr::render
{
	
	class Material
	{
	public:
		std::string m_name;

		oakvr::render::Color m_vAmbient = 0xffffffff;
		oakvr::render::Color m_vDiffuse = 0xffffffff;
		oakvr::render::Color m_vSpecular = 0xffffffff;

		//int m_nShininess;
		//float m_fAlpha;

		//bool m_bSpecular;
		std::string m_shaderName = "";

	public:
		explicit Material(std::string &);
		explicit Material(const char *);
		~Material(void);
	};
} // namespace oakvr
