#pragma once

#include <vector>
#include <list>
#include <cstdint>

#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "AABB.h"


namespace ro3d
{
	namespace Render
	{
		class Material;
		class IndexBuffer;
		class VertexBuffer;

		class Mesh
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

			// Configuration methods; must be called before InitMesh
			void SetNumVertices(unsigned int numVertices);
			void SetHasNormals(bool bHasNormals);
			void SetNumTexCoordsPerVertex(unsigned int numTexCoordsPerVertex);
			void SetNumMaterials(unsigned int numMaterials);

			// Allocates memory for all the buffers inside this mesh
			void InitMesh();

			const ro3d::Render::AABB &GetBoundingBox();

		public:
			static std::list<Mesh *> *GetMeshList();
			static void ReleaseMeshList();
			static std::list<Mesh *> *s_meshes;
			static bool s_bDeleteListIfEmpty;

			std::vector<MeshElement> m_vMeshElements;
			uint8_t *m_pVertexData;
			uint32_t *m_pIndexData;
			uint32_t m_vertexFormat;
			uint32_t m_vertexSize;
			uint32_t m_vertexCount;
			uint32_t m_indexCount;

			std::vector<uint32_t> m_vMaterials;

			bool m_bHasNormals;

			uint32_t m_numFaces;
			uint32_t m_numMaterials;

			ro3d::Render::AABB m_aabb;
		};

	} // namespace Render
} // namespace ro3d

