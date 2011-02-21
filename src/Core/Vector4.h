#pragma once
#include "d3dx9math.h"

class CVector4 : public D3DXVECTOR4
{
public:
	float Length() const;
	CVector4 *Normalize();
	float Dot(const CVector4 &vec);
	
	CVector4(D3DXVECTOR4 &vec) { x = vec.x; y = vec.y; z = vec.z; w = vec.w; }
	CVector4() : D3DXVECTOR4() {}
	CVector4(float fX, float fY, float fZ, float fW) { x = fX; y = fY; z = fZ; w = fW; }
	CVector4(const class CVector3 &vec);

};

