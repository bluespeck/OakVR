#include "Renderer.h"
#include "MeshManager.h"
#include "Mesh.h"

namespace oakvr
{
	namespace render
	{
		void Renderer::RegisterMesh(std::shared_ptr<Mesh> pMesh)
		{
			m_pMeshManager->AddMesh(pMesh);
		}
	}	// namespace render
}	// namespace oakvr