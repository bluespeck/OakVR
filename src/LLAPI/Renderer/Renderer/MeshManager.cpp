#include "MeshManager.h"
#include "Mesh.h"

namespace oakvr
{
	namespace render
	{
		MeshManager::MeshManager()
		{

		}

		MeshManager::~MeshManager()
		{

		}

		void MeshManager::AddMesh(std::shared_ptr<Mesh> pMesh)
		{
			m_meshes.push_back(pMesh);
		}

		void MeshManager::Clear()
		{
			m_meshes.clear();
		}

		void MeshManager::AddOneFrameMesh(std::shared_ptr<Mesh> pMesh)
		{
			m_oneFrameMeshes.push_back(pMesh);
		}

		void MeshManager::ClearOneFrameMeshes()
		{
			m_oneFrameMeshes.clear();
		}

		
	}
}