#pragma once

#include "d3dx9math.h"

class CVector3 :	public D3DXVECTOR3
{
public:
	float Length() const;
	CVector3 *Normalize();
	float Dot(const CVector3 &vec);
	CVector3 Cross(const CVector3 &vec) const;

	CVector3(D3DXVECTOR3 &vec) { x = vec.x; y = vec.y; z = vec.z; }
	CVector3() : D3DXVECTOR3() {}
	CVector3(float fX, float fY, float fZ) { x = fX; y = fY; z = fZ; }
	CVector3(const class CVector4 &vec);

};