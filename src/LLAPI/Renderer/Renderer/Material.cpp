
#include "Material.h"

namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		Material::Material(std::string &name)
			: m_shaderName(name)
		{
		}

		// --------------------------------------------------------------------------------
		Material::~Material()
		{
		}
	} // namespace render
} //oakvr
