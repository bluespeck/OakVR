#pragma once

#include "Mesh.h"

#include <vector>
#include <memory>


namespace oakvr
{
	namespace render
	{

		class MeshManager
		{
		public:
			typedef std::vector<std::shared_ptr<Mesh>> MeshVector;

			MeshManager();
			~MeshManager();

			void AddMesh(std::shared_ptr<Mesh> pMesh);
			void AddOneFrameMesh(std::shared_ptr<Mesh> pMesh);
			void ClearOneFrameMeshes();
			void Clear();

			void RemoveMesh(std::shared_ptr<Mesh> pMesh);

			auto SortMeshesByMaterial()->Mesh::MeshElementVector;
			auto SortByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward)->Mesh::MeshElementVector;

			auto GetMeshes()->MeshVector & { return m_meshes; }
			auto GetOneFrameMeshes()->MeshVector & { return m_oneFrameMeshes; }
		private:
			MeshVector m_meshes;
			MeshVector m_oneFrameMeshes;
		};
	}
}
