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
			void Clear();

			MeshVector & GetMeshes() { return m_meshes; }
		private:
			MeshVector m_meshes;
		};
	}
}
