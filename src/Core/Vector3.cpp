
#include "Vector3.h"
#include "Vector4.h"

float CVector3::Length() const
{ 
	return D3DXVec3Length(this); 
}


CVector3 *CVector3::Normalize()
{
	return (CVector3 *)D3DXVec3Normalize(this, this);
}

float CVector3::Dot(const CVector3 &vec)
{
	return D3DXVec3Dot(this, &vec);
}

CVector3 CVector3::Cross(const CVector3 &vec) const
{
	CVector3 result;
	D3DXVec3Cross(&result, this, &vec);
	return result;
}

CVector3::CVector3(const CVector4 &vec)
{ 
	x = vec.x;
	y = vec.y;
	z = vec.z;
}