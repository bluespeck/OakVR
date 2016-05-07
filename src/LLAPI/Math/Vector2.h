#pragma once

#include "BaseTypes.h"
#include <initializer_list>
#include <utility>

namespace oakvr
{
	namespace math
	{
		class Vector2
		{
		public:
			using BaseType = Real;

			// constructors
			Vector2() noexcept : x{ 0 }, y{ 0 } {};
			Vector2(BaseType x, BaseType y) noexcept : x{ x }, y{ y } {}; // no default parameters because we want the user to either specify all fields or none at all
			Vector2(const std::initializer_list<BaseType> &coords) noexcept;
			Vector2(const std::pair<BaseType, BaseType> &coords) noexcept;
			explicit Vector2( const BaseType *arr ) noexcept;

			Vector2(const class Vector3 &vec) noexcept;

			// cast operators
			operator BaseType * () noexcept;
			operator const BaseType * () const noexcept;

			// assignment operators
			auto operator += ( const Vector2 &vec ) noexcept -> Vector2&;
			auto operator -= ( const Vector2 &vec ) noexcept -> Vector2&;
			auto operator *= ( BaseType scalar ) noexcept -> Vector2&;
			auto operator /= ( BaseType scalar ) noexcept -> Vector2&;

			// unary operators
			auto operator + () const noexcept -> Vector2;
			auto operator - () const noexcept -> Vector2;

			// binary operators
			auto operator + ( const Vector2 &vec ) const noexcept -> Vector2;
			auto operator - ( const Vector2 &vec ) const noexcept -> Vector2;
			auto operator * ( BaseType scalar ) const noexcept -> Vector2;
			auto operator / ( BaseType scalar ) const noexcept -> Vector2;

			friend auto operator * ( BaseType scalar, const Vector2 &vec ) noexcept -> Vector2;

			// equality operators
			auto operator == ( const Vector2 &vec ) const noexcept -> bool;
			auto operator != ( const Vector2 &vec ) const noexcept -> bool;

			// other methods
			auto GetLength() const noexcept -> BaseType;
			auto GetSquareLength() const noexcept -> BaseType;
			auto GetNormalized() const noexcept -> Vector3;
			Vector2 Normalize() const noexcept;
			auto Dot( const Vector2 &vec ) const noexcept -> BaseType;

			// static constants
			static Vector2 One;
			static Vector2 Zero;

			// members
			BaseType x, y;
		};

		auto operator * ( Vector2::BaseType scalar, const Vector2 &vec ) noexcept -> Vector2;

	} // namespace Math
}
