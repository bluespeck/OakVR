#include "Mesh.h"

using namespace Oak3D::Math;
namespace Oak3D
{
	namespace Core
	{
		Mesh::Mesh(void)
			: m_pVertices(nullptr)
			, m_pIndices(nullptr)
			, m_pNormals(nullptr)
			, m_pMaterials(nullptr)
			, m_pMaterialRanges(nullptr)
			, m_numIndices(0)
			, m_numVertices(0)
			, m_numTexCoordsPerVertex(0)
			, m_bHasNormals(false)

		{
			for(unsigned int i = 0; i < 8; ++i)
			{
				m_pTexCoords[i] = nullptr;
			}
		}

		Mesh::~Mesh(void)
		{
			if(m_pVertices)
				delete[] m_pVertices;
			if(m_pIndices)
				delete[] m_pIndices;
			if(m_pNormals)
				delete[] m_pNormals;
			if(m_pMaterials)
				delete[] m_pMaterials;
			if(m_pMaterialRanges)
				delete[] m_pMaterialRanges;
			for(unsigned int i = 0; i < m_numTexCoordsPerVertex; ++i)
				if(m_pTexCoords[i])
					delete[] m_pTexCoords[i];
		}

		void Mesh::SetNumVertices(unsigned int numVertices)
		{
			m_numVertices = numVertices;
		}

		void Mesh::SetHasNormals(bool bHasNormals)
		{
			m_bHasNormals = bHasNormals;
		}

		void Mesh::SetNumTexCoordsPerVertex(unsigned int numTexCoordsPerVertex)
		{
			m_numTexCoordsPerVertex = numTexCoordsPerVertex;
		}

		void Mesh::SetNumMaterials(unsigned int numMaterials)
		{
			m_numMaterials = numMaterials;
		}

		// Allocates memory for all the buffers inside this mesh
		void Mesh::InitMesh()
		{
			if(m_numVertices)
			{
				m_pVertices = new Vector3[m_numVertices];
			}

			if(m_numIndices)
			{	
				m_pIndices = new unsigned int[m_numIndices];
			}

			if(m_numMaterials)
			{
				m_pMaterials = new unsigned int[m_numMaterials];
				m_pMaterialRanges = new unsigned int[m_numMaterials];

			}

			if(m_bHasNormals)
			{
				m_pNormals = new Vector3[m_numVertices];
			}

			if(m_numTexCoordsPerVertex > 0)
			{
				for(unsigned int i = 0; i < m_numTexCoordsPerVertex; ++i)
				{
					m_pTexCoords[i] = new Vector2[m_numVertices];
				}
			}
		}
	} // namespace Core
}