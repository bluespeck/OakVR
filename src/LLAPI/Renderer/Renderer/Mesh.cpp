#include "Mesh.h"
#include "Utils/Types.h"

namespace oakvr
{
	namespace render
	{
		// --------------------------------------------------------------------------------
		Mesh::Mesh(const StringId &name)
			:m_name( name )
		{
		}

		// --------------------------------------------------------------------------------
		Mesh::~Mesh()
		{	
		}

		void Mesh::AddMeshElement(const sp<MeshElement> &pMeshElem)
		{
			pMeshElem->m_pMesh = this;
			m_vMeshElements.push_back(pMeshElem);
		}

	} // namespace render
}// namespace oakvr
