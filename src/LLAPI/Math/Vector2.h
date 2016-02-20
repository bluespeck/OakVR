#pragma once

#include <initializer_list>
#include <utility>

namespace oakvr
{
	namespace math
	{
		class Vector2
		{
		public:
			// constructors
			Vector2() {};			
			Vector2( float x, float y );
			Vector2(const std::pair<float, float> &coords);
			Vector2(const std::initializer_list<float> &coords);
			Vector2( const class Vector3 &vec );
			Vector2( const float *arr );

			// cast operators
			operator float * ();
			operator const float * () const;

			// assignment operators
			auto operator += ( const Vector2 &vec ) -> Vector2&;
			auto operator -= ( const Vector2 &vec ) -> Vector2&;
			auto operator *= ( float scalar ) -> Vector2&;
			auto operator /= ( float scalar ) -> Vector2&;

			// unary operators
			auto operator + () const -> Vector2;
			auto operator - () const -> Vector2;

			// binary operators
			auto operator + ( const Vector2 &vec ) const -> Vector2;
			auto operator - ( const Vector2 &vec ) const -> Vector2;
			auto operator * ( float scalar ) const -> Vector2;
			auto operator / ( float scalar ) const -> Vector2;

			friend auto operator * ( float scalar, const Vector2 &vec ) -> Vector2;

			// equality operators
			auto operator == ( const Vector2 &vec ) const -> bool;
			auto operator != ( const Vector2 &vec ) const -> bool;

			// other methods
			auto GetLength() const -> float;
			auto GetSquareLength() const -> float;
			auto GetNormalized() const -> Vector3;
			Vector2 Normalize() const;
			auto Dot( const Vector2 &vec ) const -> float;

			// static constants
			static Vector2 One;
			static Vector2 Zero;

			// members
			float x, y;
		};

		auto operator * ( float scalar, const Vector2 &vec ) -> Vector2;

	} // namespace Math
}
