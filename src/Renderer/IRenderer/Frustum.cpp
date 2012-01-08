
#include "Frustum.h"

namespace Oak3D
{
	namespace Render
	{
		

	Frustum::Frustum(void)
	{		
	}

/*
#include "Plane.h"
#include "Vector3.h"
#include "Matrix.h"

Frustum::Frustum(void)
{
	// default values for FOV, aspect ration and near and far distances
	m_fFOV = D3DX_PI / 4.0f;
	m_fAspect = 1.0f;
	m_fNear = 1.0f;
	m_fFar = 1000.0f;
	m_vecForward = CVector3(0.0f, 0.0f, 1.0f);
	m_vecUp = CVector3(0.0f, 1.0f, 0.0f);
	m_vecRight = CVector3(1.0f, 0.0f, 0.0f);
}

bool Frustum::Inside(const CVector3 &point) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].Inside(point) )
			return false;

	return true;
}

bool Frustum::Inside(const CVector3 &point, float fRadius) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].Inside(point, fRadius) )
			return false;

	return true;
}

bool Frustum::Inside(const CAABB &aabb) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].Inside(aabb) )
			return false;

	return true;
}

bool Frustum::Inside(const CAABB &aabb, float fRadius) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].Inside(aabb, fRadius) )
			return false;

	return true;
}

bool Frustum::CompletlyInside(const CAABB &aabb) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].CompletlyInside(aabb) )
			return false;

	return true;
}

bool Frustum::CompletlyInside(const CAABB &aabb, float fRadius) const
{
	for(int i = 0; i < eFP_NumPlanes; ++i)
		if( !m_planes[i].CompletlyInside(aabb, fRadius) )
			return false;
}

void Frustum::Init(float fFOV, float fAspect, float fNear, float fFar)
{
	m_fFOV = fFOV;
	m_fAspect = fAspect;
	m_fNear = fNear;
	m_fFar = fFar;
}

void Frustum::ComputePlanesFromMatrix(const CMatrix &m)
{

	// Left clipping plane
	m_planes[eFP_Left].a = (m._14 + m._11);
	m_planes[eFP_Left].b = (m._24 + m._21);
	m_planes[eFP_Left].c = (m._34 + m._31);
	m_planes[eFP_Left].d = (m._44 + m._41);

	// Right clipping plane
	m_planes[eFP_Right].a = (m._14 - m._11);
	m_planes[eFP_Right].b = (m._24 - m._21);
	m_planes[eFP_Right].c = (m._34 - m._31);
	m_planes[eFP_Right].d = (m._44 - m._41);

	// Top clipping plane
	m_planes[eFP_Top].a = (m._14 - m._12);
	m_planes[eFP_Top].b = (m._24 - m._22);
	m_planes[eFP_Top].c = (m._34 - m._32);
	m_planes[eFP_Top].d = (m._44 - m._42);

	// Bottom clipping plane
	m_planes[eFP_Bottom].a = (m._14 + m._12);
	m_planes[eFP_Bottom].b = (m._24 + m._22);
	m_planes[eFP_Bottom].c = (m._34 + m._32);
	m_planes[eFP_Bottom].d = (m._44 + m._42);

	// Near clipping plane
	m_planes[eFP_Near].a = (m._14 + m._13);
	m_planes[eFP_Near].b = (m._24 + m._23);
	m_planes[eFP_Near].c = (m._34 + m._33);
	m_planes[eFP_Near].d = (m._44 + m._43);

	// Far clipping plane
	m_planes[eFP_Far].a = (m._14 - m._13);
	m_planes[eFP_Far].b = (m._24 - m._23);
	m_planes[eFP_Far].c = (m._34 - m._33);
	m_planes[eFP_Far].d = (m._44 - m._43);

	// Normalize the planes
	for ( unsigned long int i = 0; i < 6; i++ ) 
		D3DXPlaneNormalize( &m_planes[i], &m_planes[i] );
}
*/

	} // namespace Render
} // namespace Oak3D