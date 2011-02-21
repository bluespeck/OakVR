
#include "Matrix.h"

CMatrix CMatrix::g_matIdentity(D3DXMATRIX(1,0,0,0,	0,1,0,0,	0,0,1,0,	0,0,0,1));

void CMatrix::SetPosition(const CVector3 &vecPosition)
{
	m[3][0] = vecPosition.x;
	m[3][1] = vecPosition.y;
	m[3][2] = vecPosition.z;
	m[3][3] = 1.0f;
}

void CMatrix::SetPosition(const CVector4 &vecPosition)
{
	m[3][0] = vecPosition.x;
	m[3][1] = vecPosition.y;
	m[3][2] = vecPosition.z;
	m[3][3] = vecPosition.w;
}

CVector3 CMatrix::GetPosition() const
{
	return CVector3(m[3][0], m[3][1], m[3][2]);
}

CVector4 CMatrix::Transform(CVector4 &vec) const
{
	CVector4 vecOut;
	D3DXVec4Transform(&vecOut, &vec, this);
	return vecOut;
}

CVector3 CMatrix::Transform(CVector3 &vec) const
{
	CVector4 vecOut;
	D3DXVec3Transform(&vecOut, &vec, this);
	return CVector3(vecOut.x, vecOut.y, vecOut.z);
}

CMatrix CMatrix::Inverse() const
{
	CMatrix matOut;
	D3DXMatrixInverse(&matOut, NULL, this);
	return matOut;
}

void CMatrix::BuildTranslation(const CVector3 &vecPosition)
{
	*this = g_matIdentity;
	m[3][0] = vecPosition.x;
	m[3][1] = vecPosition.y;
	m[3][2] = vecPosition.z;
}

void CMatrix::BuildTranslation(float x, float y, float z)
{
	*this = g_matIdentity;
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

void CMatrix::BuildRotationX(float radians)
{
	D3DXMatrixRotationX(this, radians);
}

void CMatrix::BuildRotationY(float radians)
{
	D3DXMatrixRotationY(this, radians);
}

void CMatrix::BuildRotationZ(float radians)
{
	D3DXMatrixRotationZ(this, radians);
}

void CMatrix::BuildYawPitchRoll(float yawRadians, float pitchRadians, float rollRadians)
{
	D3DXMatrixRotationYawPitchRoll(this, yawRadians, pitchRadians, rollRadians);
}

void CMatrix::Multiply(CMatrix &out, const CMatrix &a, const CMatrix &b)
{
	D3DXMatrixMultiply(&out, &a, &b);
}

void CMatrix::Transform(CVector4 &out, const CVector4 &vec, const CMatrix &mat)
{
	D3DXVec4Transform(&out, &vec, &mat);
}
void CMatrix::Transform(CVector3 &out, const CVector3 &vec, const CMatrix &mat)
{
	CVector4 vecTemp;
	D3DXVec3Transform(&vecTemp, &vec, &mat);
	out.x = vecTemp.x;
	out.y = vecTemp.y;
	out.z = vecTemp.z;
}

CMatrix::CMatrix(D3DXMATRIX &mat)
{
	memcpy(&m, &mat.m, sizeof(mat.m));
}

CMatrix::CMatrix(void) : D3DXMATRIX()
{
}