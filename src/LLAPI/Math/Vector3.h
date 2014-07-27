#pragma once

#include <initializer_list>

namespace oakvr
{
	namespace math
	{
		class Matrix;

		class Vector3
		{
		public:
			// constructors
			Vector3() {};			
			Vector3( float x, float y, float z );
			Vector3(const std::initializer_list<float> &coords);
			Vector3( const class Vector4 &vec );
			Vector3( const float *arr );
			
			// cast operators
			inline operator float * ();
			inline operator const float * () const;

			// assignment operators
			//Vector3& operator = ( const Vector3 &vec );
			Vector3& operator += ( const Vector3 &vec );
			Vector3& operator -= ( const Vector3 &vec );
			Vector3& operator *= ( float scalar );
			Vector3& operator /= ( float scalar );

			// unary operators
			Vector3 operator + () const;
			Vector3 operator - () const;

			// binary operators
			Vector3 operator + ( const Vector3 &vec ) const;
			Vector3 operator - ( const Vector3 &vec ) const;
			Vector3 operator * ( float scalar ) const;
			Vector3 operator / ( float scalar ) const;
			Vector3 operator * ( const Matrix &mat ) const;
			friend Vector3 operator *(const Matrix &mat, const Vector3 &vec);
			friend Vector3 operator * ( float scalar, const Vector3 &vec );

			// equality operators
			bool operator != ( const Vector3 &vec ) const;
			bool operator ==(const Vector3& vec) const;

			// other methods
			float GetLength() const;
			Vector3 GetNormalized() const;
			float Normalize();
			float Dot( const Vector3 &vec ) const;
			Vector3 Cross( const Vector3 &vec ) const;

			// members
			float x, y, z;
		};

		Vector3 operator * ( float scalar, const Vector3 &vec );
		Vector3 operator * ( const Matrix &mat, const Vector3 &vec );
		
		//------------------------------------------------------
		// cast operators
		// --------------------------------------------------------------------------------
		Vector3::operator float *()
		{
			return &x;
		}

		// --------------------------------------------------------------------------------
		Vector3::operator const float *() const
		{
			return &x;
		}
	} // namespace Math
}
