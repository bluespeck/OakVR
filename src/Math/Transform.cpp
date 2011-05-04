#include "Transform.h"

#include <cmath>

namespace Oak3D
{
	namespace Math
	{

		Transform::Transform(void)
		{			
		}

		void Transform::SetIdentity()
		{
			// Init to identity transform
			_11 = _22 = _33 = _44 = 1.0f;
			_12 = _13 = _14 = 0.0f;
			_21 = _23 = _24 = 0.0f;
			_31 = _32 = _34 = 0.0f;
			_41 = _42 = _43 = 0.0f;
		}

		void Transform::SetRotationX(float angle)
		{
			_11 = 1.0f;	_12 = _13 = _14 = 0.0f;
			_21 = 0.0f;	_22 = std::cos(angle); _23 = -std::sin(angle);	_24 = 0.0f;
			_31 = 0.0f;	_32 = -_23;	_33 = _22; _34 = 0.0f;
			_41 = _42 = _43 = 0.0f; _44 = 1.0f;
		}

		void Transform::SetRotationY(float angle)
		{
			_11 = std::cos(angle); _12 = 0.0f; _13 = std::sin(angle); _14 = 0.0f;
			_21 = 0.0f;	_22 = 1.0f; _23 = _24 = 0.0f;
			_31 = -_13;	_32 = 0.0f;	_33 = _11; _34 = 0.0f;
			_41 = _42 = _43 = 0.0f; _44 = 1.0f;
		}

		void Transform::SetRotationZ(float angle)
		{
			_11 = std::cos(angle); _12 = -std::sin(angle); _13 = _14 = 0.0f;
			_21 = -_12;	_22 = _11; _23 = _24 = 0.0f;
			_31 = _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
			_41 = _42 = _43 = 0.0f; _44 = 1.0f;
		}

		Transform CreateRotationX(float angle)
		{
			Transform t;
			t._11 = 1.0f;	t._12 = t._13 = t._14 = 0.0f;
			t._21 = 0.0f;	t._22 = std::cos(angle); t._23 = -std::sin(angle);	t._24 = 0.0f;
			t._31 = 0.0f;	t._32 = -t._23;	t._33 = t._22; t._34 = 0.0f;
			t._41 = t._42 = t._43 = 0.0f; t._44 = 1.0f;
			
			return t;
		}

		Transform CreateRotationY(float angle)
		{
			Transform t;
			t._11 = std::cos(angle); t._12 = 0.0f; t._13 = std::sin(angle); t._14 = 0.0f;
			t._21 = 0.0f;	t._22 = 1.0f; t._23 = t._24 = 0.0f;
			t._31 = -t._13;	t._32 = 0.0f;	t._33 = t._11; t._34 = 0.0f;
			t._41 = t._42 = t._43 = 0.0f; t._44 = 1.0f;

			return t;
		}

		Transform CreateRotationZ(float angle)
		{
			Transform t;
			t._11 = std::cos(angle); t._12 = -std::sin(angle); t._13 = t._14 = 0.0f;
			t._21 = -t._12;	t._22 = t._11; t._23 = t._24 = 0.0f;
			t._31 = t._32 = 0.0f; t._33 = 1.0f; t._34 = 0.0f;
			t._41 = t._42 = t._43 = 0.0f; t._44 = 1.0f;

			return t;
		}
	}
}