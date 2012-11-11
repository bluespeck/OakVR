#pragma once

namespace ro3d
{
	namespace Math
	{
		class Vector2
		{
		public:
			// constructors
			Vector2() {};			
			Vector2( float x, float y );
			Vector2( const class Vector3 &vec );
			Vector2( const float *arr );

			// cast operators
			operator float * ();
			operator const float * () const;

			// assignment operators
			Vector2& operator += ( const Vector2 &vec );
			Vector2& operator -= ( const Vector2 &vec );
			Vector2& operator *= ( float scalar );
			Vector2& operator /= ( float scalar );

			// unary operators
			Vector2 operator + () const;
			Vector2 operator - () const;

			// binary operators
			Vector2 operator + ( const Vector2 &vec ) const;
			Vector2 operator - ( const Vector2 &vec ) const;
			Vector2 operator * ( float scalar ) const;
			Vector2 operator / ( float scalar ) const;

			friend Vector2 operator * ( float scalar, const Vector2 &vec );

			// equality operators
			bool operator == ( const Vector2 &vec ) const;
			bool operator != ( const Vector2 &vec ) const;

			// other methods
			float Length() const;
			Vector2 Normalize() const;
			float Dot( const Vector2 &vec ) const;

			// members
			float x, y;
		};

		Vector2 operator * ( float scalar, const Vector2 &vec );

	} // namespace Math
}
