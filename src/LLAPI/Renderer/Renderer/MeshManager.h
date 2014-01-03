#pragma once

#include <vector>
#include <memory>

#include "Mesh.h"

namespace oakvr
{
	namespace render
	{
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
