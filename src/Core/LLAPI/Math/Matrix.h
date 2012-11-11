#pragma once

namespace Oak3D
{
	namespace Math
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

			inline operator float* ();
			inline operator const float* () const;

			void SetInverseOfRotoTranslation();
			void SetInverse();			
			void SetYawPitchRoll(float yaw, float pitch, float roll);
			
			Matrix CreateInverseOfRotoTranslation() const;
			Matrix CreateInverse() const;
			
			Matrix operator+(const Matrix &mat) const;
			Matrix operator*(const Matrix &mat) const;
			
			static Matrix CreateYawPitchRoll(float yaw, float pitch, float roll);
			static Matrix CreatePerspectiveProjectionMatrix(float fov, float aspect, float znear, float zfar);
			static Matrix CreateOthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
			static Matrix CreateIdentityMatrix();
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
	} // namespace Oak3D
} // namespace Oak3D
