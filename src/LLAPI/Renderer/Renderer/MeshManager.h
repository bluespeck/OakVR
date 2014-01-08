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
			MeshManager();
			~MeshManager();

			void AddMesh(std::shared_ptr<Mesh> pMesh);
			void Clear();
		private:
			std::vector<std::shared_ptr<Mesh>> m_meshes;
		};
	}
}
