/*
 *  Mesh.h
 *
 *  Created by Mircea Ispas
 *
 */

#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include "RenderEngineDefines.h"
#include "RenderEngine.h"
#include "Resource.h"
#include "AABB.h"
#include "BoundingSphere.h"

class Texture;

class CIndexBuffer
{
	public:
		CIndexBuffer()
		{
			m_data = NULL;
			m_id = 0;
			m_count = 0;
		}

		void	Create(UINT count);
		void	Lock(UINT offsetToLock, UINT sizeToLock, void **ppBuff, DWORD flags);
		void	Unlock();
		void	Release();

		void*	m_data;
		UINT	m_id;
		UINT	m_count;
};

class CVertexBuffer
{
	public:
		CVertexBuffer()
		{
			m_data = NULL;
			m_format = 0;
			m_vertexSize = 0;
			m_id = 0;
			m_count = 0;
		}

		void	Create(UINT count, DWORD vertexFormat);
		void	Lock(UINT offsetToLock, UINT sizeToLock, void **ppBuff, DWORD flags);
		void	Unlock();
		void	Release();

		void*	m_data;
		DWORD	m_format;
		UINT	m_vertexSize;
		UINT	m_id;
		UINT	m_count;
};

class CMaterial
{
	public:
		CMaterial();		

		Texture*	m_texture0;
		Texture*	m_texture1;

		void Release();

		BlendMode	m_blendMode;
		CMatrix		m_UVAnimation0;
		CMatrix		m_UVAnimation1;
};

class CMeshElementInfo
{
public:
	CMeshElementInfo();
	~CMeshElementInfo();				
	UINT			m_startIndex;
	UINT			m_indexCount;
	RenderMode		m_renderMode;
	
	Path			m_path0, m_path1;
	BlendMode		m_matBlendMode;
};

class CMeshInfo : public Resource
{
public:
	friend int LoadMeshThreadProc(void *pData);

	CMeshInfo();
	~CMeshInfo();

	void			Load();
	void			Reload();
	void			Release();

	CVertexBuffer*				m_pVertexBuffer;
	CIndexBuffer*				m_pIndexBuffer;
	std::vector<CMeshElementInfo *> m_vElements;

	CAABB						m_aabb;
	CBoundingSphere				m_boundingSphere;
	UINT						m_numFaces;
};

class CMesh
{
public:	
	friend class CRenderEngine;

	CMesh();
	~CMesh();
	
	void Init(const Path &path);
	bool IsLoaded();
	bool RayInteresction( const CVector3 &ray, const CVector3 &origin, float *pU = NULL, float *pV = NULL, float *pDist = NULL );

	const CAABB &GetBoundingBox();
	const CBoundingSphere &GetBoundingSphere();

protected:
	void LoadMaterials();

private:
		CMeshInfo *m_pMeshInfo;
		std::vector<CMaterial*>	m_vMaterials;
		bool m_bMaterialsInitialised;
};

#endif