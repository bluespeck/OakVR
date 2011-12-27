#include <assimp.hpp>
#include <aiPostProcess.h>
#include <aiScene.h>

#include <cassert>
#include <cvt/wstring>
#include <codecvt>
#include <string>

#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Oak3D/Engine.h"
#include "Core/Parallel/Thread.h"

using namespace std;
using namespace Oak3D::Math;

namespace Oak3D
{
	namespace Render
	{

		static uint32_t LoadMeshThreadProc(void *pData)
		{
			Assimp::Importer importer;
			importer.SetPropertyInteger(AI_CONFIG_IMPORT_TER_MAKE_UVS,1);
			//importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE,80.0f);
	
			// remove lines and points from loaded model
			importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );

			// will be needed for a loading progress bar
			//importer.SetPropertyInteger(AI_CONFIG_GLOB_MEASURE_TIME,1);

			Mesh *pMesh = (Mesh *)pData;

			std::string  path  = pMesh->GetId().GetStrId();

			// Start the loading process
			pMesh->SetState(Oak3D::Core::IResource::eRS_Loading);
	
			aiScene *pScene = (aiScene*)importer.ReadFile(path.c_str(),
				aiProcess_GenSmoothNormals			| // generate smooth normal vectors if not existing
				aiProcess_SplitLargeMeshes			| // split large, unrenderable meshes into submeshes
				aiProcess_Triangulate				| // triangulate polygons with more than 3 edges
				aiProcess_ConvertToLeftHanded		| // convert everything to D3D left handed space
				aiProcess_PreTransformVertices		| // pretransform all vertices with local transformation; destroys animations
				aiProcess_SortByPType				| // make 'clean' meshes which consist of a single typ of primitives
				0);

			assert(pScene && "Error reading file");	

			// find out what type of primitives we have in the mesh; switch(pAIMesh->mPrimitiveTypes)
	
			int nVertexCount = 0;
			int nIndexCount = 0;
			pMesh->m_vMeshElements.resize(pScene->mNumMeshes);

			// initialize our mesh using the aiScene meshes; also find total number of vertices and indices
			for(uint32_t i = 0; i < pScene->mNumMeshes; ++i)
			{
				aiMesh *pAIMesh = pScene->mMeshes[i];

				// All aiMesh vertices in the scene are held in one place for our mesh
				// and the aiMesh counts have to be added together
				nVertexCount += pAIMesh->mNumVertices;

				// Initialize our mesh element corresponding to the ith aiMesh
				//pMesh->m_vMeshElements[i].m_renderMode = eRM_Triangles;
				pMesh->m_vMeshElements[i].m_startIndex = nIndexCount;
				pMesh->m_vMeshElements[i].m_indexCount = pAIMesh->mNumFaces * 3;
		
				nIndexCount += pMesh->m_vMeshElements[i].m_indexCount;		
		
				aiString texPath="";
				aiMaterial *pAIMaterial = pScene->mMaterials[pAIMesh->mMaterialIndex];
		
				// TODO add material
				//pAIMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), texPath);		
				//pMesh->m_vMeshElements[i].m_path0 = texPath.data;

				//texPath = "";
				//pAIMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(1), texPath);		
				//pMeshInfo->m_vElements[i]->m_path1 = texPath.data;
				
				//pMeshInfo->m_vElements[i]->m_matBlendMode = eBM_BlendNone;
			}

			// Initialize and fill buffers
			if(pMesh->m_pVertexBuffer)
			{
				pMesh->m_pVertexBuffer->Release();
				delete pMesh->m_pVertexBuffer;
			}
			if(pMesh->m_pIndexBuffer)
			{
				pMesh->m_pIndexBuffer->Release();
				delete pMesh->m_pIndexBuffer;
			}

			pMesh->m_pVertexBuffer = new VertexBuffer();
			pMesh->m_pIndexBuffer = new IndexBuffer();
	
			bool bHasPositions, bHasNormals, bHasTextureCoords0, bHasTextureCoords1, bHasVertexColors;
			uint32_t nFormat =	((bHasPositions			=	pScene->mMeshes[0]->HasPositions())			? VertexBuffer::eVF_XYZ		: 0)|
								((bHasNormals			=	pScene->mMeshes[0]->HasNormals())			? VertexBuffer::eVF_Normal	: 0)|
								((bHasTextureCoords0	=	pScene->mMeshes[0]->HasTextureCoords(0))	? VertexBuffer::eVF_Tex0	: 0)|
								((bHasTextureCoords1	=	pScene->mMeshes[0]->HasTextureCoords(1))	? VertexBuffer::eVF_Tex1	: 0)|
								((bHasVertexColors		=	pScene->mMeshes[0]->HasVertexColors(0))		? VertexBuffer::eVF_Diffuse	: 0);
	
			pMesh->m_pVertexBuffer->SetVertexSize(sizeof(float) * (3 * (bHasPositions + bHasNormals + bHasTextureCoords0 + bHasTextureCoords1) + 4 * bHasVertexColors));
			pMesh->m_pVertexBuffer->Create(nVertexCount, nFormat);		
			pMesh->m_pIndexBuffer->Create(nIndexCount);

			char *pIB = NULL;	
			char *pVB = NULL;		
			char *pVBData = NULL;
			char *pIBData = NULL;

			pMesh->m_pVertexBuffer->Lock((void **)&pVB);	
			pMesh->m_pIndexBuffer->Lock((void **)&pIB);
		
			pIBData = pIB;	
			pVBData = pVB;

			uint32_t nFaceCount = 0;	

			Oak3D::Math::Vector3 vecLBF = Oak3D::Math::Vector3(0, 0, 0);
			Vector3 vecRTB = Oak3D::Math::Vector3(0, 0, 0);

			for(uint32_t i = 0; i < pScene->mNumMeshes; ++i)
			{
				aiMesh *pAIMesh = pScene->mMeshes[i];
				memset(pVBData, 0, pAIMesh->mNumVertices * pMesh->m_pVertexBuffer->GetVertexSize());
		
				for(uint32_t j = 0; j < pAIMesh->mNumVertices; ++j)
				{
					// add vertex position
					memcpy(pVBData, &pAIMesh->mVertices[j], 3 * sizeof(float));
					pVBData += 3 * sizeof(float);			
			
					{	// compute bounding box
						if(vecLBF.x > pAIMesh->mVertices[j].x)
							vecLBF.x = pAIMesh->mVertices[j].x;
						else
							if(vecRTB.x < pAIMesh->mVertices[j].x)
								vecRTB.x = pAIMesh->mVertices[j].x;

						if(vecLBF.y > pAIMesh->mVertices[j].y)
							vecLBF.y = pAIMesh->mVertices[j].y;
						else
							if(vecRTB.y < pAIMesh->mVertices[j].y)
								vecRTB.y = pAIMesh->mVertices[j].y;

						if(vecLBF.z > pAIMesh->mVertices[j].z)
							vecLBF.z = pAIMesh->mVertices[j].z;
						else
							if(vecRTB.z < pAIMesh->mVertices[j].z)
								vecRTB.z = pAIMesh->mVertices[j].z;
					}


					// add vertex normal
					if(bHasNormals)
					{
						memcpy(pVBData, &pAIMesh->mNormals[j], 3 * sizeof(float));
						pVBData += 3 * sizeof(float);				
					}
					// add vertex texCoords 0
					if(bHasTextureCoords0)
					{
						memcpy(pVBData, &pAIMesh->mTextureCoords[0][j], 3 * sizeof(float));
						pVBData += 3 * sizeof(float);
					}
			
			
					// add vertex texCoords 1
					if(bHasTextureCoords1)
					{
						memcpy(pVBData, &pAIMesh->mTextureCoords[1][j], 3 * sizeof(float));
						pVBData += 3 * sizeof(float);
					}
					// add vertex diffuse color
					if(bHasVertexColors)
					{
				
						//DWORD dwB = (DWORD) (pAIMesh->mColors[0][j].b * 255.0f + 0.5f);
						//DWORD dwG = (DWORD) (pAIMesh->mColors[0][j].g * 255.0f + 0.5f);
						//DWORD dwR = (DWORD) (pAIMesh->mColors[0][j].r * 255.0f + 0.5f);
						//DWORD dwA = (DWORD) (pAIMesh->mColors[0][j].a * 255.0f + 0.5f);
						//DWORD color = (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
						//memcpy(pVBData, &color, sizeof(DWORD));
				
						*pVBData	 =  (uint8_t) (pAIMesh->mColors[0][j].b * 255.0f + 0.5f);
						*(pVBData+1) =  (uint8_t) (pAIMesh->mColors[0][j].g * 255.0f + 0.5f);
						*(pVBData+2) =  (uint8_t) (pAIMesh->mColors[0][j].r * 255.0f + 0.5f);
						*(pVBData+3) =  (uint8_t) (pAIMesh->mColors[0][j].a * 255.0f + 0.5f);
						pVBData += sizeof(uint32_t);
					}
				}

				nFaceCount += pAIMesh->mNumFaces;

				for(uint32_t j = 0; j < pAIMesh->mNumFaces; ++j)
				{
					((uint32_t *)pIBData)[0] = pAIMesh->mFaces[j].mIndices[0] + pMesh->m_vMeshElements[i].m_startIndex;
					((uint32_t *)pIBData)[1] = pAIMesh->mFaces[j].mIndices[1] + pMesh->m_vMeshElements[i].m_startIndex;
					((uint32_t *)pIBData)[2] = pAIMesh->mFaces[j].mIndices[2] + pMesh->m_vMeshElements[i].m_startIndex;			
					pIBData += 3 * sizeof(uint32_t);
				}		
			}
	
			pMesh->m_pIndexBuffer->Unlock();
			pMesh->m_pVertexBuffer->Unlock();	
	
			pMesh->m_numFaces = nFaceCount;
			pMesh->m_aabb.m_vecLeftBottomFront = vecLBF;
			pMesh->m_aabb.m_vecRightTopBack = vecRTB;
	
			// compute bounding sphere
			/*
			float x;
			float y;
			float z;
			float cx;
			float cy;
			float cz;
			float sqrRadius = 0.f;
			float sqrDist;

			pMesh->m_boundingSphere.m_center = (vecLBF + vecRTB) * .5f;
			cx = pMesh->m_boundingSphere.m_center.x;
			cy = pMesh->m_boundingSphere.m_center.y;
			cz = pMesh->m_boundingSphere.m_center.z;
			for(uint32_t i = 0; i < pScene->mNumMeshes; ++i)
			{
				aiMesh *pAIMesh = pScene->mMeshes[i];
				for(uint32_t j = 0; j < pAIMesh->mNumVertices; ++j)
				{
					x = pAIMesh->mVertices[j].x;
					y = pAIMesh->mVertices[j].y;
					z = pAIMesh->mVertices[j].z;
					// check if the current vertex is outside the bounding sphere
					sqrDist = (cx - x) * (cx - x) + (cy - y) * (cy - y) + (cz - z) * (cz - z);
					if(sqrRadius < sqrDist)
					{
						sqrRadius = sqrDist;
					}
				}
			}
			pMesh->m_boundingSphere.m_radius = sqrtf(sqrRadius);
			*/

			// Mesh loading has finished
			pMesh->SetState(Oak3D::Core::IResource::eRS_Ready);

			return 0;
		}

		Mesh::Mesh()
		: m_pVertexBuffer(NULL)
		, m_pIndexBuffer(NULL)	
		{
		//	m_type = Resource::eTypeMeshInfo;
		}

		Mesh::~Mesh()
		{	
		}

		Mesh::MeshElement::MeshElement()
		: m_startIndex(0)
		, m_indexCount(0)
		{
		}

		void Mesh::Init(const std::wstring &path)
		{
			
		}

		void Mesh::Load()
		{	
			new Oak3D::Core::Thread(LoadMeshThreadProc, this);
		}

		void Mesh::Reload()
		{

		}

		void Mesh::Release()
		{
			SetState(eRS_Loading);

			if(m_pVertexBuffer)
			{
				m_pVertexBuffer->Release();
				delete m_pVertexBuffer;
				m_pVertexBuffer = NULL;
			}

			if(m_pIndexBuffer)
			{
				m_pIndexBuffer->Release();		
				delete m_pIndexBuffer;
				m_pIndexBuffer = NULL;
			}
			/* TODO need pointers here?
			for(uint32_t i = 0, n = m_vMeshElements.size(); i < n; ++i)
			{	
				delete m_vMeshElements[i];
				m_vMeshElements[i] = NULL;
			}
			*/
			m_vMeshElements.clear();
		
			SetState(eRS_Released);
			delete this;
		}
		/*
		Mesh::Mesh()
		{
			//m_pMesh = NULL;
			m_bMaterialsInitialised = false;
		}

		Mesh::~Mesh()
		{
			for(uint32_t i = 0, s = m_pMesh->m_vMeshElements.size(); i < s; ++i)
			{
				m_vMaterials[i]->Release();
			}
			ReleaseMesh(m_pMeshInfo);
			m_pMeshInfo = NULL;
			m_vMaterials.clear();	
		}
		
		
		void Mesh::LoadMaterials()
		{
			m_vMaterials.resize(m_pMeshInfo->m_vMeshElements.size());
			for(uint32_t i = 0, s = m_pMeshInfo->m_vMeshElements.size(); i < s; ++i)
			{
				m_vMaterials[i]= new CMaterial();
				if(m_pMeshInfo->m_vElements[i]->m_path0 != "")
					m_vMaterials[i]->m_texture0 = MakeTexture(m_pMesh->m_vMeshElements[i]->m_path0);
		
				if(m_pMeshInfo->m_vElements[i]->m_path1 != "")
					m_vMaterials[i]->m_texture1 = MakeTexture(m_pMesh->m_vMeshElements[i]->m_path1);
		
				m_vMaterials[i]->m_blendMode = m_pMeshInfo->m_vElements[i]->m_matBlendMode;		
		
			}
			m_bMaterialsInitialised = true;
		}

		void Mesh::Init(const Path &path)
		{
			m_pMeshInfo = MakeMeshInfo(path);
			m_bMaterialsInitialised = false;
		}
		
		bool Mesh::RayInteresction( const CVector3 &ray, const CVector3 &origin, float *pU, float *pV, float *pDist )
		{
			if(!m_pMeshInfo->IsReady())
				return false;

			BYTE *pVB	= NULL;
			UINT *pIB	= NULL;

			// Check if the ray intersects the object's bounding box
			if(!D3DXBoxBoundProbe( &m_pMeshInfo->m_aabb.m_vecLeftBottomFront, &m_pMeshInfo->m_aabb.m_vecRightTopBack, &origin, &ray))
				return false;

			D3DXVECTOR3 v1, v2, v3;
		
			m_pMeshInfo->m_pVertexBuffer->Lock(0, 0, (void **)&pVB, 0);
			m_pMeshInfo->m_pIndexBuffer->Lock(0, 0, (void **)&pIB, 0);

			bool bIntersects = false;

			// Treat index buffer as a triangle list
			for(UINT i = 0; i < m_pMeshInfo->m_pIndexBuffer->m_count; i += 3)
			{
				v1 = *(CVector3 *)&pVB[pIB[i]		* m_pMeshInfo->m_pVertexBuffer->m_vertexSize];
				v2 = *(CVector3 *)&pVB[pIB[i + 1]	* m_pMeshInfo->m_pVertexBuffer->m_vertexSize];
				v3 = *(CVector3 *)&pVB[pIB[i + 2]	* m_pMeshInfo->m_pVertexBuffer->m_vertexSize];
		
				if (D3DXIntersectTri( &v1, &v2, &v3, &origin, &ray , pU, pV, pDist ))
				{
					bIntersects = true;
					break;
				}
			}

			m_pMeshInfo->m_pIndexBuffer->Unlock();
			m_pMeshInfo->m_pVertexBuffer->Unlock();

			return bIntersects;
		}
		*/

		const Core::AABB &Mesh::GetBoundingBox()
		{
			return m_aabb;
		}

		/*
		const CBoundingSphere &Mesh::GetBoundingSphere()
		{
			return m_pMeshInfo->m_boundingSphere;
		}
		

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
		}*/

		
	} // namespace Render
}// namespace Oak3D
