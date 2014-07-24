#pragma once

#include <initializer_list>

namespace oakvr
{
	namespace math
	{
		class Vector4
		{
		public:
			// constructors
			Vector4() {};			
			Vector4( float x, float y, float z, float w );
			Vector4(const std::initializer_list<float> &coords);
			Vector4( const float *arr );

			// cast operators
			operator float * ();
			operator const float * () const;

			// assignment operators
			Vector4& operator += ( const Vector4 &vec );
			Vector4& operator -= ( const Vector4 &vec );
			Vector4& operator *= ( float scalar );
			Vector4& operator /= ( float scalar );

			// unary operators
			Vector4 operator + () const;
			Vector4 operator - () const;

			// binary operators
			Vector4 operator + ( const Vector4 &vec ) const;
			Vector4 operator - ( const Vector4 &vec ) const;
			Vector4 operator * ( float scalar ) const;
			Vector4 operator / ( float scalar ) const;

			friend Vector4 operator * ( float scalar, const Vector4 &vec );

			// equality operators
			bool operator == ( const Vector4 &vec ) const;
			bool operator != ( const Vector4 &vec ) const;

			// other methods
			float Length() const;
			Vector4 Normalize() const;
			float Dot( const Vector4 &vec ) const;			

			// members
			float x, y, z, w;
		};

		Vector4 operator * ( float scalar, const Vector4 &vec );

	} // namespace Math
}
