#pragma once

#include "d3dx9math.h"

class CVector2 : public D3DXVECTOR2
{
public:
	float Length() const;
	CVector2 *Normalize();
	float Dot(const CVector2 &vec);

	CVector2(D3DXVECTOR3 &vec) { x = vec.x; y = vec.y; }
	CVector2() : D3DXVECTOR2() {}
	CVector2(float fX, float fY) { x = fX; y = fY; }
	CVector2(const class CVector3 &vec);
};
