
#include "Vector2.h"
#include "Vector3.h"

float CVector2::Length() const
{ 
	return D3DXVec2Length(this); 
}


CVector2 *CVector2::Normalize()
{
	return (CVector2 *)D3DXVec2Normalize(this, this);
}

float CVector2::Dot(const CVector2 &vec)
{
	return D3DXVec2Dot(this, &vec);
}

CVector2::CVector2(const CVector3 &vec)
{ 
	x = vec.x;
	y = vec.y;
}
