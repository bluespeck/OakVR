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
			auto operator += ( const Vector3 &vec ) -> Vector3&;
			auto operator -= ( const Vector3 &vec ) -> Vector3&;
			auto operator *= ( float scalar ) -> Vector3&;
			auto operator /= ( float scalar ) -> Vector3&;

			// unary operators
			auto operator + () const -> Vector3;
			auto operator - () const -> Vector3;

			// binary operators
			auto operator + ( const Vector3 &vec ) const -> Vector3;
			auto operator - ( const Vector3 &vec ) const -> Vector3;
			auto operator * ( float scalar ) const -> Vector3;
			auto operator / ( float scalar ) const -> Vector3;
			auto operator * ( const Matrix &mat ) const -> Vector3;
			friend auto operator *(const Matrix &mat, const Vector3 &vec) -> Vector3;
			friend auto operator * ( float scalar, const Vector3 &vec ) -> Vector3;

			// equality operators
			auto operator != ( const Vector3 &vec ) const -> bool;
			auto operator ==(const Vector3& vec) const -> bool;

			// other methods
			auto GetLength() const -> float;
			auto GetNormalized() const -> Vector3;
			auto Normalize() -> float;
			auto Dot( const Vector3 &vec ) const -> float;
			auto Cross( const Vector3 &vec ) const -> Vector3;

			// static constants
			static Vector3 One;
			static Vector3 Zero;

			// members
			float x, y, z;
		};

		auto operator * ( float scalar, const Vector3 &vec ) -> Vector3;
		auto operator * ( const Matrix &mat, const Vector3 &vec ) -> Vector3;
		
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
