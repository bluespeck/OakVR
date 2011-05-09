
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MESH_H__
#define __OAK3D_INCLUDE_MESH_H__

#include <vector>

#include "IResource.h"
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Utils/AABB.h"


namespace Oak3D
{
	namespace Core
	{
		class Material;
		class IndexBuffer;
		class VertexBuffer;

		class Mesh : public IResource
		{
		public:

			class MeshElement
			{
			public:
				MeshElement();
				
				uint32_t m_startIndex;
				uint32_t m_indexCount;
				uint32_t m_materialIndex;
			};

			Mesh(void);
			~Mesh(void);

			// overrides
			void Init(const std::wstring &path);
			void Load();
			void Reload();
			void Release();

			// Configuration methods; must be called before InitMesh
			void SetNumVertices(unsigned int numVertices);
			void SetHasNormals(bool bHasNormals);
			void SetNumTexCoordsPerVertex(unsigned int numTexCoordsPerVertex);
			void SetNumMaterials(unsigned int numMaterials);

			// Allocates memory for all the buffers inside this mesh
			void InitMesh();

			const Utils::AABB &GetBoundingBox();

		public:
			std::vector<MeshElement> m_vMeshElements;
			VertexBuffer *m_pVertexBuffer;
			IndexBuffer *m_pIndexBuffer;
			std::vector<uint32_t> m_vMaterials;

			bool		m_bHasNormals;

			uint32_t m_numMeshElements;
			uint32_t m_numFaces;
			uint32_t m_numMaterials;

			Oak3D::Utils::AABB m_aabb;
		};

	} // namespace Core
}

#endif
