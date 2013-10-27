#pragma once

#include "MeshElement.h"

#include <memory>
#include <vector>
#include <cstdint>

namespace oakvr
{
	namespace render
	{
		class Mesh
		{
		public:
			Mesh();
			~Mesh();

			// Configuration methods; must be called before InitMesh
			void SetNumVertices(unsigned int numVertices);
			void SetHasNormals(bool bHasNormals);
			void SetNumTexCoordsPerVertex(unsigned int numTexCoordsPerVertex);
			void SetNumMaterials(unsigned int numMaterials);

			//const oakvr::render::AABB &GetBoundingBox();

			static std::vector<std::shared_ptr<Mesh>> &GetMeshes();
			static void ReleaseMeshes();

		private:
			static std::vector<std::shared_ptr<Mesh>> s_meshes;
			std::vector<std::shared_ptr<MeshElement>> m_vMeshElements;
			std::shared_ptr<Material> m_meshMaterial;	// defaultin case a submesh doesn't have a material, it will use this one

		};

	} // namespace Render
} // namespace oakvr

