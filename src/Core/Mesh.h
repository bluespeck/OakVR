
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_MESH_H__
#define __OAK3D_INCLUDE_MESH_H__

#include <assimp.h>
#include <aiPostProcess.h>
#include <aiScene.h>

//#include "IResource.h"

#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace Oak3D
{
	namespace Core
	{
		class Material;

		class Mesh// : public IResource
		{
		public:
			Mesh(void);
			~Mesh(void);

			// Configuration methods; must be called before InitMesh
			void SetNumVertices(unsigned int numVertices);
			void SetHasNormals(bool bHasNormals);
			void SetNumTexCoordsPerVertex(unsigned int numTexCoordsPerVertex);
			void SetNumMaterials(unsigned int numMaterials);

			// Allocates memory for all the buffers inside this mesh
			void InitMesh();

		public:
			Oak3D::Math::Vector3	*m_pVertices;
			Oak3D::Math::Vector3	*m_pNormals;
			Oak3D::Math::Vector2	*m_pTexCoords[8];

			unsigned int		*m_pIndices;
			unsigned int		*m_pMaterials;
			unsigned int		*m_pMaterialRanges;		// {mat(1)_start, mat(2)_start, ... mat(m_numMaterials)_start}

			bool		m_bHasNormals;

			unsigned int		m_numVertices;
			unsigned int		m_numIndices;
			unsigned int		m_numTexCoordsPerVertex;	
			unsigned int		m_numMaterials;
		};

	} // namespace Core
}

#endif
