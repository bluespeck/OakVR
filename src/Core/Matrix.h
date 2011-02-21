#pragma once

#include <d3dx9math.h>

#include "Vector4.h"
#include "Vector3.h"

class CMatrix : public D3DXMATRIX
{
public:

	void SetPosition(const CVector3 &vecPosition);
	void SetPosition(const CVector4 &vecPosition);

	CVector3 GetPosition() const;

	CVector4 Transform(CVector4 &vec) const;
	CVector3 Transform(CVector3 &vec) const;
	CMatrix Inverse() const;
	void BuildTranslation(const CVector3 &vecPosition);
	void BuildTranslation(float x, float y, float z);
	void BuildRotationX(float radians);
	void BuildRotationY(float radians);
	void BuildRotationZ(float radians);
	void BuildYawPitchRoll(float yawRadians, float pitchRadians, float rollRadians);
	// Build rotation quaternion ?
		
	CMatrix(D3DXMATRIX &mat);
	CMatrix(void);

	static void Multiply(CMatrix &out, const CMatrix &a, const CMatrix &b);
	static void Transform(CVector4 &out, const CVector4 &vec, const CMatrix &mat);
	static void Transform(CVector3 &out, const CVector3 &vec, const CMatrix &mat);

	static CMatrix g_matIdentity;
};