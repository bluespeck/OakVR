#include "Mesh.h"

using namespace Oak3D::Math;
/*
static int LoadMeshThreadProc(void *pData)
{
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_IMPORT_TER_MAKE_UVS,1);
	//importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE,80.0f);
	
	// Remove lines and points from loaded model
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );

	// Will be needed for a loading progress bar
	//importer.SetPropertyInteger(AI_CONFIG_GLOB_MEASURE_TIME,1);

	CMeshInfo *pMeshInfo = (CMeshInfo *)pData;
	char *szPath = pMeshInfo->GetPath().CopyToCharArray();
	
	// Start the loading process
	pMeshInfo->m_status = CMeshInfo::eStatusLoading;
	
	aiScene *pScene = (aiScene*)importer.ReadFile(szPath,
		aiProcess_GenSmoothNormals			| // generate smooth normal vectors if not existing
		aiProcess_SplitLargeMeshes			| // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate				| // triangulate polygons with more than 3 edges
		aiProcess_ConvertToLeftHanded		| // convert everything to D3D left handed space
		aiProcess_PreTransformVertices		| // pretransform all vertices with local transformation; destroys animations
		aiProcess_SortByPType				| // make 'clean' meshes which consist of a single typ of primitives
		0);

	ASSERT(pScene, "Error reading file");
	delete szPath;

	// find out what type of primitives we have in the mesh; switch(pAIMesh->mPrimitiveTypes)
	
	int nVertexCount = 0;
	int nIndexCount = 0;
	pMeshInfo->m_vElements.resize(pScene->mNumMeshes);

	// initialize our mesh using the aiScene meshes; also find total number of vertices and indices
	for(UINT i = 0; i < pScene->mNumMeshes; ++i)
	{
		aiMesh *pAIMesh = pScene->mMeshes[i];

		// All aiMesh vertices in the scene are held in one place for our mesh
		// and the aiMesh counts have to be added together
		nVertexCount += pAIMesh->mNumVertices;

		// Initialize our mesh element corresponding to the ith aiMesh
		pMeshInfo->m_vElements[i] = new CMeshElementInfo;
		pMeshInfo->m_vElements[i]->m_renderMode = eRM_Triangles;
		pMeshInfo->m_vElements[i]->m_startIndex = nIndexCount;
		pMeshInfo->m_vElements[i]->m_indexCount = pAIMesh->mNumFaces * 3;
		
		nIndexCount += pMeshInfo->m_vElements[i]->m_indexCount;		
		
		aiString texPath="";
		aiMaterial *pAIMaterial = pScene->mMaterials[pAIMesh->mMaterialIndex];
		
		pAIMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), texPath);		
		pMeshInfo->m_vElements[i]->m_path0 = texPath.data;

		texPath = "";
		pAIMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(1), texPath);		
		pMeshInfo->m_vElements[i]->m_path1 = texPath.data;
				
		pMeshInfo->m_vElements[i]->m_matBlendMode = eBM_BlendNone;
	}

	// Initialize and fill buffers
	if(pMeshInfo->m_pVertexBuffer)
	{
		pMeshInfo->m_pVertexBuffer->Release();
		delete pMeshInfo->m_pVertexBuffer;
	}
	if(pMeshInfo->m_pIndexBuffer)
	{
		pMeshInfo->m_pIndexBuffer->Release();
		delete pMeshInfo->m_pIndexBuffer;
	}

	pMeshInfo->m_pVertexBuffer = new CVertexBuffer();
	pMeshInfo->m_pIndexBuffer = new CIndexBuffer();
	
	bool bHasPositions, bHasNormals, bHasTextureCoords0, bHasTextureCoords1, bHasVertexColors;
	DWORD nFormat =	((bHasPositions			=	pScene->mMeshes[0]->HasPositions())			? eVF_XYZ		: 0)|
					((bHasNormals			=	pScene->mMeshes[0]->HasNormals())			? eVF_Normal	: 0)|
					((bHasTextureCoords0	=	pScene->mMeshes[0]->HasTextureCoords(0))	? eVF_Tex0		: 0)|
					((bHasTextureCoords1	=	pScene->mMeshes[0]->HasTextureCoords(1))	? eVF_Tex1		: 0)|
					((bHasVertexColors		=	pScene->mMeshes[0]->HasVertexColors(0))		? eVF_Diffuse	: 0);
	
	pMeshInfo->m_pVertexBuffer->m_vertexSize = sizeof(float) * (3 * (bHasPositions + bHasNormals + bHasTextureCoords0 + bHasTextureCoords1) + 4 * bHasVertexColors);
	pMeshInfo->m_pVertexBuffer->Create(nVertexCount, nFormat);		
	pMeshInfo->m_pIndexBuffer->Create(nIndexCount);

	char *pIB = NULL;	
	char *pVB = NULL;		
	char *pVBData = NULL;
	char *pIBData = NULL;

	pMeshInfo->m_pVertexBuffer->Lock(0, 0, (void **)&pVB, 0);	
	pMeshInfo->m_pIndexBuffer->Lock(0, 0, (void **)&pIB, 0);
		
	pIBData = pIB;	
	pVBData = pVB;

	UINT nFaceCount = 0;	

	CVector3 vecLBF = CVector3(0, 0, 0);
	CVector3 vecRTB = CVector3(0, 0, 0);

	for(UINT i = 0; i < pScene->mNumMeshes; ++i)
	{
		aiMesh *pAIMesh = pScene->mMeshes[i];
		ZeroMemory(pVBData, pAIMesh->mNumVertices * pMeshInfo->m_pVertexBuffer->m_vertexSize );
		
		for(UINT j = 0; j < pAIMesh->mNumVertices; ++j)
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
				
				*pVBData	 =  (BYTE) (pAIMesh->mColors[0][j].b * 255.0f + 0.5f);
				*(pVBData+1) =  (BYTE) (pAIMesh->mColors[0][j].g * 255.0f + 0.5f);
				*(pVBData+2) =  (BYTE) (pAIMesh->mColors[0][j].r * 255.0f + 0.5f);
				*(pVBData+3) =  (BYTE) (pAIMesh->mColors[0][j].a * 255.0f + 0.5f);
				pVBData += sizeof(DWORD);
			}
		}

		nFaceCount += pAIMesh->mNumFaces;

		for(UINT j = 0; j < pAIMesh->mNumFaces; ++j)
		{
			((UINT *)pIBData)[0] = pAIMesh->mFaces[j].mIndices[0] + pMeshInfo->m_vElements[i]->m_startIndex;
			((UINT *)pIBData)[1] = pAIMesh->mFaces[j].mIndices[1] + pMeshInfo->m_vElements[i]->m_startIndex;
			((UINT *)pIBData)[2] = pAIMesh->mFaces[j].mIndices[2] + pMeshInfo->m_vElements[i]->m_startIndex;			
			pIBData += 3 * sizeof(UINT);
		}		
	}
	
	pMeshInfo->m_pIndexBuffer->Unlock();
	pMeshInfo->m_pVertexBuffer->Unlock();	
	
	pMeshInfo->m_numFaces = nFaceCount;
	pMeshInfo->m_aabb.m_vecLeftBottomFront = vecLBF;
	pMeshInfo->m_aabb.m_vecRightTopBack = vecRTB;
	
	// compute bounding sphere
	float x;
	float y;
	float z;
	float cx;
	float cy;
	float cz;
	float sqrRadius = 0.f;
	float sqrDist;

	pMeshInfo->m_boundingSphere.m_center = (vecLBF + vecRTB) * .5f;
	cx = pMeshInfo->m_boundingSphere.m_center.x;
	cy = pMeshInfo->m_boundingSphere.m_center.y;
	cz = pMeshInfo->m_boundingSphere.m_center.z;
	for(UINT i = 0; i < pScene->mNumMeshes; ++i)
	{
		aiMesh *pAIMesh = pScene->mMeshes[i];
		for(UINT j = 0; j < pAIMesh->mNumVertices; ++j)
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
	pMeshInfo->m_boundingSphere.m_radius = sqrtf(sqrRadius);

	// Mesh loading has finished
	pMeshInfo->m_status = CMeshInfo::eStatusReady;

	return 0;
}

void CVertexBuffer::Create(UINT count, DWORD vertexFormat)
{
	m_count = count;
	m_format = vertexFormat;
	CEngine::GetRenderEngine()->CreateVertexBuffer(this);
}

void CVertexBuffer::Lock(UINT offsetToLock, UINT sizeToLock, void **ppBuff, DWORD flags)
{
	CEngine::GetRenderEngine()->LockVertexBuffer(this, offsetToLock, sizeToLock, ppBuff, flags);
}

void CVertexBuffer::Unlock()
{
	CEngine::GetRenderEngine()->UnlockVertexBuffer(this);
}

void CVertexBuffer::Release()
{
	CEngine::GetRenderEngine()->ReleaseVertexBuffer(this);
}

void CIndexBuffer::Create(UINT count)
{
	m_count = count;
	CEngine::GetRenderEngine()->CreateIndexBuffer(this);
}

void CIndexBuffer::Lock(UINT offsetToLock, UINT sizeToLock, void **ppBuff, DWORD flags)
{
	CEngine::GetRenderEngine()->LockIndexBuffer(this, offsetToLock, sizeToLock, ppBuff, flags);
}

void CIndexBuffer::Unlock()
{
	CEngine::GetRenderEngine()->UnlockIndexBuffer(this);
}

void CIndexBuffer::Release()
{
	CEngine::GetRenderEngine()->ReleaseIndexBuffer(this);
}

CMeshInfo::CMeshInfo()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)	
{
	m_type = Resource::eTypeMeshInfo;
	m_asyncLoad = true;
}

CMeshInfo::~CMeshInfo()
{	
}

CMeshElementInfo::CMeshElementInfo()
: m_startIndex(0)
, m_indexCount(0)
, m_renderMode(eRM_Triangles)
{
}

CMeshElementInfo::~CMeshElementInfo()
{	
}

CMaterial::CMaterial()
: m_texture0(NULL)
, m_texture1(NULL)
, m_blendMode(eBM_BlendNone)
{
	m_UVAnimation0 = CMatrix::g_matIdentity;
	m_UVAnimation1 = CMatrix::g_matIdentity;
}

void CMaterial::Release()
{
	if(m_texture0)
	{
		ReleaseTexture(m_texture0);
	}

	if(m_texture1)
	{
		ReleaseTexture(m_texture1);
	}

	delete this;
}

void CMeshInfo::Load()
{	
	Thread::Create(LoadMeshThreadProc, this);
}
void CMeshInfo::Reload()
{

}
void CMeshInfo::Release()
{
	m_status = eStatusLoading;

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
	
	for(UINT i = 0, n = m_vElements.size(); i < n; ++i)
	{	
		delete m_vElements[i];
		m_vElements[i] = NULL;
	}
	m_vElements.clear();
		
	m_status = eStatusReleased;
	delete this;
}

CMesh::CMesh()
{
	m_pMeshInfo = NULL;
	m_bMaterialsInitialised = false;
}

CMesh::~CMesh()
{
	for(UINT i = 0, s = m_pMeshInfo->m_vElements.size(); i < s; ++i)
	{
		m_vMaterials[i]->Release();
	}
	ReleaseMeshInfo(m_pMeshInfo);
	m_pMeshInfo = NULL;
	m_vMaterials.clear();	
}

bool CMesh::IsLoaded()
{
	bool bMeshInfoLoaded = m_pMeshInfo->IsReady();
	if( bMeshInfoLoaded && !m_bMaterialsInitialised)
		LoadMaterials();	// initialise materials after mesh info is loaded

	return bMeshInfoLoaded && m_bMaterialsInitialised;
}

void CMesh::LoadMaterials()
{
	m_vMaterials.resize(m_pMeshInfo->m_vElements.size());
	for(UINT i = 0, s = m_pMeshInfo->m_vElements.size(); i < s; ++i)
	{
		m_vMaterials[i]= new CMaterial();
		if(m_pMeshInfo->m_vElements[i]->m_path0 != "")
			m_vMaterials[i]->m_texture0 = MakeTexture(m_pMeshInfo->m_vElements[i]->m_path0);
		
		if(m_pMeshInfo->m_vElements[i]->m_path1 != "")
			m_vMaterials[i]->m_texture1 = MakeTexture(m_pMeshInfo->m_vElements[i]->m_path1);
		
		m_vMaterials[i]->m_blendMode = m_pMeshInfo->m_vElements[i]->m_matBlendMode;		
		
	}
	m_bMaterialsInitialised = true;
}

void CMesh::Init(const Path &path)
{
	m_pMeshInfo = MakeMeshInfo(path);
	m_bMaterialsInitialised = false;
}

bool CMesh::RayInteresction( const CVector3 &ray, const CVector3 &origin, float *pU, float *pV, float *pDist )
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

const CAABB &CMesh::GetBoundingBox()
{
	return m_pMeshInfo->m_aabb;
}

const CBoundingSphere &CMesh::GetBoundingSphere()
{
	return m_pMeshInfo->m_boundingSphere;
}
*/

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