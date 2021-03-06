#pragma once

#include "Vector3.h"
#include <initializer_list>

namespace oakvr
{
	namespace math
	{

		class Matrix
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
			Matrix();
			Matrix( float *m );
			Matrix(const std::initializer_list<float> &initList);
			Matrix(float diagValue);

			inline operator float* ();
			inline operator const float* () const;

			auto GetTransposed() const -> Matrix;
			auto GetInverse() const -> Matrix;
			
			auto operator+(const Matrix &mat) const -> Matrix;
			auto operator*(const Matrix &mat) const -> Matrix;
			
			auto SetRotationX(float angle) -> void;
			auto SetRotationY(float angle) -> void;
			auto SetRotationZ(float angle) -> void;
			auto SetIdentity() -> void;

			auto Transpose() -> void;
			auto Invert() -> void;
			auto SetYawPitchRoll(float yaw, float pitch, float roll) -> void;

			// Matrix builders
			static auto RotationX(float angle) -> Matrix;
			static auto RotationY(float angle) -> Matrix;
			static auto RotationZ(float angle) -> Matrix;
			static auto RotationAxisRightHanded(float angle, const Vector3& axis) -> Matrix; // note that axis has to be normalized beforehand
			static auto YawPitchRoll(float yaw, float pitch, float roll)->Matrix;

			static auto Translation(float x, float y, float z) -> Matrix;
			static auto Translation(const Vector3 &vec) -> Matrix;

			static auto Scale(float x, float y, float z) -> Matrix;
			static auto Scale(float scale) -> Matrix;
			static auto Scale(const Vector3 &vec) -> Matrix;

			static auto PerspectiveProjection(float fov, float width, float height, float znear, float zfar) -> Matrix;
			static auto PerspectiveProjection(float fov, float aspectY, float znear, float zfar) -> Matrix;
			static auto OrthographicProjection(float left, float right, float bottom, float top, float near, float far) -> Matrix;

			// Neutral matrices
			static Matrix Identity;
			static Matrix Zero;
		};

		// --------------------------------------------------------------------------------
		Matrix::operator float* ()
		{
			return (float *) &_11;
		}

		// --------------------------------------------------------------------------------	
		Matrix::operator const float* () const
		{
			return (const float *) &_11;
		}
	} // namespace oakvr
} // namespace oakvr
