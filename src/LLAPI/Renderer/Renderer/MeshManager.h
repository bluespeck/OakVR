#pragma once

#include <vector>
#include <memory>

namespace oakvr
{
	namespace render
	{
		class Mesh;

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

			MeshVector & GetMeshes() { return m_meshes; }
			MeshVector & GetOneFrameMeshes() { return m_oneFrameMeshes; }
		private:
			MeshVector m_meshes;
			MeshVector m_oneFrameMeshes;
		};
	}
}
