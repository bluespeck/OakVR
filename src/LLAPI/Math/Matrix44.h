#pragma once

#include "Vector3.h"
#include <initializer_list>

namespace oakvr::math
{

	class Matrix44
	{
	public:
		union
		{
			float m[4][4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
		Matrix44();
		Matrix44(float* m);
		Matrix44(const std::initializer_list<float>& initList);
		Matrix44(float diagValue);

		inline operator float* ();
		inline operator const float* () const;

		auto GetTransposed() const->Matrix44;
		auto GetInverse() const->Matrix44;

		auto operator+(const Matrix44& mat) const->Matrix44;
		auto operator*(const Matrix44& mat) const->Matrix44;

		auto SetRotationX(float angle) -> void;
		auto SetRotationY(float angle) -> void;
		auto SetRotationZ(float angle) -> void;
		auto SetIdentity() -> void;

		auto Transpose() -> void;
		auto Invert() -> void;
		auto SetYawPitchRoll(float yaw, float pitch, float roll) -> void;

		// Matrix44 builders
		static auto RotationX(float angle)->Matrix44;
		static auto RotationY(float angle)->Matrix44;
		static auto RotationZ(float angle)->Matrix44;
		static auto RotationAxisRightHanded(float angle, const Vector3& axis)->Matrix44; // note that axis has to be normalized beforehand
		static auto YawPitchRoll(float yaw, float pitch, float roll)->Matrix44;

		static auto Translation(float x, float y, float z)->Matrix44;
		static auto Translation(const Vector3& vec)->Matrix44;

		static auto Scale(float x, float y, float z)->Matrix44;
		static auto Scale(float scale)->Matrix44;
		static auto Scale(const Vector3& vec)->Matrix44;

		static auto PerspectiveProjection(float fov, float width, float height, float znear, float zfar)->Matrix44;
		static auto PerspectiveProjection(float fov, float aspectY, float znear, float zfar)->Matrix44;
		static auto OrthographicProjection(float left, float right, float bottom, float top, float near, float far)->Matrix44;

		// Neutral matrices
		static Matrix44 Identity;
		static Matrix44 Zero;
	};

	// --------------------------------------------------------------------------------
	Matrix44::operator float* ()
	{
		return (float*)&_11;
	}

	// --------------------------------------------------------------------------------	
	Matrix44::operator const float* () const
	{
		return (const float*)&_11;
	}
}