#pragma once

#include "Plane.h"

class CFrustum
{
public:
	enum FrustumPlane { eFP_Left, eFP_Right, eFP_Top, eFP_Bottom, eFP_Near, eFP_Far, eFP_NumPlanes };
	
	CFrustum();

	bool Inside(const CVector3 &point) const;
	bool Inside(const CVector3 &point, float fRadius) const;
	bool Inside(const CAABB &aabb) const;
	bool Inside(const CAABB &aabb, float fRadius) const;
	bool CompletlyInside(const CAABB &aabb) const;
	bool CompletlyInside(const CAABB &aabb, float fRadius) const;
	
	const CPlane &GetPlane(FrustumPlane ePlane);
	
	void Init(float fFOV, float fAspect, float fNear, float fFar);
	void ComputePlanesFromMatrix(const class CMatrix &mat);

	void SetFOV( float fFOV )			{ m_fFOV	= fFOV;		}
	void SetAspect( float fAspect )		{ m_fAspect = fAspect;	}
	void SetNearDistance( float fNear ) { m_fNear	= fNear;	}
	void SetFarDistance( float fFar )	{ m_fFar	= fFar;		}
	
	
		
public:
	CPlane m_planes[eFP_NumPlanes];	// planes of the frustum in camera space
	CVector3 m_nearClip[4];	// vertices of the near clip plane in camera space
	CVector3 m_farClip[4];	// vertices of the far clip plane in camera space

	float m_fFOV;	// field of view in radians
	float m_fAspect;// aspect ratio; w/h
	float m_fNear;	// near clip distance
	float m_fFar;	// far clip distance

	CVector3 m_vecForward;
	CVector3 m_vecUp;
	CVector3 m_vecRight;
	CVector3 m_vecPosition;
};

