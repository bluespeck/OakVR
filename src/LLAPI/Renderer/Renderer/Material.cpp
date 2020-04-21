
#include "Material.h"

namespace oakvr::render
{
	// --------------------------------------------------------------------------------
	Material::Material(std::string &name)
		: m_shaderName(name)
	{
	}

	// --------------------------------------------------------------------------------
	Material::Material(const char *name)
		: m_shaderName(name)
	{
	}

	// --------------------------------------------------------------------------------
	Material::~Material()
	{
	}
}
