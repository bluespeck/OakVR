#pragma once

#include "Vector3.h"

namespace oakvr
{
	namespace math
	{

		class Matrix
		{
		public:
			union
			{
				struct
				{
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};
				float m[4][4];
			};
			Matrix();
			Matrix( float *m );
			Matrix(float diagValue);

			inline operator float* ();
			inline operator const float* () const;

			Matrix GetTransposed() const;
			Matrix GetInverse() const;
			
			Matrix operator+(const Matrix &mat) const;
			Matrix operator*(const Matrix &mat) const;
			
			void SetRotationX(float angle);
			void SetRotationY(float angle);
			void SetRotationZ(float angle);
			void SetIdentity();

			void Transpose();
			void Invert();
			void SetYawPitchRoll(float yaw, float pitch, float roll);

			static Matrix RotationX(float angle);
			static Matrix RotationY(float angle);
			static Matrix RotationZ(float angle);
			static Matrix RotationAxisRightHanded(float angle, const Vector3& axis); // note that axis has to be normalized beforehand

			static Matrix Translation(float x, float y, float z);
			static Matrix Translation(const Vector3 &vec);
			static Matrix Scale(float x, float y, float z);
			static Matrix Scale(float scale);

			static Matrix PerspectiveProjection(float fov, float width, float height, float znear, float zfar);
			static Matrix PerspectiveProjection(float fov, float aspectY, float znear, float zfar);
			static Matrix OrthographicProjection(float left, float right, float bottom, float top, float near, float far);

			static Matrix YawPitchRoll(float yaw, float pitch, float roll);
			static Matrix Identity();
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
