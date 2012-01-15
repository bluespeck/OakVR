
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_VECTOR3_H__
#define __OAK3D_INCLUDE_CORE_VECTOR3_H__

namespace Oak3D
{
	namespace Math
	{
		class Matrix;

		class Vector3
		{
		public:
			// constructors
			Vector3() {};			
			Vector3( float x, float y, float z );
			Vector3( const class Vector4 &vec );
			Vector3( const float *arr );
			
			// cast operators
			operator float * ();
			operator const float * () const;

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

			friend Vector3 operator * ( float scalar, const Vector3 &vec );

			// equality operators
			bool operator == ( const Vector3 &vec ) const;
			bool operator != ( const Vector3 &vec ) const;

			// other methods
			float Length() const;
			Vector3 Normalize() const;
			float Dot( const Vector3 &vec ) const;
			Vector3 Cross( const Vector3 &vec ) const;

			// members
			float x, y, z;
		};

		Vector3 operator * ( float scalar, const Vector3 &vec );

	} // namespace Math
}

#endif
