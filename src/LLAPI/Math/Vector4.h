#pragma once

#include "BaseTypes.h"
#include <initializer_list>

namespace oakvr::math
{
	class Vector4
	{
	public:
		using BaseType = Real;

		// constructors
		Vector4()  noexcept : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {};
		Vector4(BaseType x, BaseType y, BaseType z, BaseType w) noexcept : x{ x }, y{ y }, z{ z }, w{ w } {}
		Vector4(const std::initializer_list<BaseType>& coords) noexcept;
		Vector4(const BaseType* arr) noexcept;

		// cast operators
		operator BaseType* () noexcept;
		operator const BaseType* () const noexcept;

		// assignment operators
		auto operator += (const Vector4& vec) noexcept->Vector4&;
		auto operator -= (const Vector4& vec) noexcept->Vector4&;
		auto operator *= (BaseType scalar) noexcept->Vector4&;
		auto operator /= (BaseType scalar) noexcept->Vector4&;

		// unary operators
		auto operator + () const noexcept->Vector4;
		auto operator - () const noexcept->Vector4;

		// binary operators
		auto operator + (const Vector4& vec) const noexcept->Vector4;
		auto operator - (const Vector4& vec) const noexcept->Vector4;
		auto operator * (BaseType scalar) const noexcept->Vector4;
		auto operator / (BaseType scalar) const noexcept->Vector4;

		friend auto operator * (BaseType scalar, const Vector4& vec) noexcept->Vector4;

		// equality operators
		auto operator == (const Vector4& vec) const noexcept -> bool;
		auto operator != (const Vector4& vec) const noexcept -> bool;

		// other methods
		auto GetLength() const noexcept->BaseType;
		auto GetSquareLength() const noexcept->BaseType;
		auto Normalize() const noexcept->Vector4;
		auto Dot(const Vector4& vec) const noexcept->BaseType;

		// static constants
		static Vector4 One;
		static Vector4 Zero;

		// members
		BaseType x, y, z, w;
	};

	auto operator * (Vector4::BaseType scalar, const Vector4& vec) noexcept->Vector4;

}