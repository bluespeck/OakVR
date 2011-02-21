#include "Vector4.h"
#include "Vector3.h"

CVector4::CVector4(const CVector3 &vec)
{ 
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = 1.0f;
}