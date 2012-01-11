
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MESH_H__
#define __OAK3D_INCLUDE_MESH_H__

#include <vector>

#include "Core/ResourceManager/IResource.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Renderer/IRenderer/AABB.h"


namespace Oak3D
{
	namespace Render
	{
		class Material;
		class IndexBuffer;
		class VertexBuffer;

		class Mesh : public Oak3D::Core::IResource
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
			void Init(const Core::StringId &id, AdditionalInitParams *pAdditionalInitParams = nullptr);
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

			const Oak3D::Render::AABB &GetBoundingBox();

		public:
			std::vector<MeshElement> m_vMeshElements;
			VertexBuffer *m_pVertexBuffer;
			IndexBuffer *m_pIndexBuffer;
			std::vector<uint32_t> m_vMaterials;

			bool		m_bHasNormals;

			uint32_t m_numMeshElements;
			uint32_t m_numFaces;
			uint32_t m_numMaterials;

			Oak3D::Render::AABB m_aabb;
		};

	} // namespace Render
} // namespace Oak3D

#endif
