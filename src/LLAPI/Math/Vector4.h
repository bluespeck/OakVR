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
			auto operator += ( const Vector4 &vec ) -> Vector4&;
			auto operator -= ( const Vector4 &vec ) -> Vector4&;
			auto operator *= ( float scalar ) -> Vector4&;
			auto operator /= ( float scalar ) -> Vector4&;

			// unary operators
			auto operator + () const -> Vector4;
			auto operator - () const -> Vector4;

			// binary operators
			auto operator + ( const Vector4 &vec ) const -> Vector4;
			auto operator - ( const Vector4 &vec ) const -> Vector4;
			auto operator * ( float scalar ) const -> Vector4;
			auto operator / ( float scalar ) const -> Vector4;

			friend auto operator * ( float scalar, const Vector4 &vec ) -> Vector4;

			// equality operators
			auto operator == ( const Vector4 &vec ) const -> bool;
			auto operator != ( const Vector4 &vec ) const -> bool;

			// other methods
			auto GetLength() const -> float;
			auto GetSquareLength() const -> float;
			auto Normalize() const -> Vector4;
			auto Dot( const Vector4 &vec ) const -> float;			

			// static constants
			static Vector4 One;
			static Vector4 Zero;

			// members
			float x, y, z, w;
		};

		auto operator * ( float scalar, const Vector4 &vec ) -> Vector4;

	} // namespace Math
}
