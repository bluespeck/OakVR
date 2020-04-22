#pragma once

#include "BaseTypes.h"
#include <initializer_list>

namespace oakvr::math
{
	class Matrix44;

	class Vector3
	{
	public:
		using BaseType = Real;

		// constructors
		Vector3() noexcept : x{ 0 }, y{ 0 }, z{ 0 } {};
		Vector3(BaseType x, BaseType y, BaseType z) noexcept; // no default parameters because we want the user to either specify all fields or none at all
		Vector3(const std::initializer_list<BaseType>& initList) noexcept;
		explicit Vector3(const BaseType* arr) noexcept;

		Vector3(const class Vector4& vec) noexcept;

		// cast operators
		inline operator BaseType* () noexcept;
		inline operator const BaseType* () const noexcept;

		// assignment operators
		auto operator += (const Vector3& vec) noexcept->Vector3&;
		auto operator -= (const Vector3& vec) noexcept->Vector3&;
		auto operator *= (BaseType scalar) noexcept->Vector3&;
		auto operator /= (BaseType scalar) noexcept->Vector3&;

		// unary operators
		auto operator + () const noexcept->Vector3;
		auto operator - () const noexcept->Vector3;

		// binary operators
		auto operator + (const Vector3& vec) const noexcept->Vector3;
		auto operator - (const Vector3& vec) const noexcept->Vector3;
		auto operator * (BaseType scalar) const noexcept->Vector3;
		auto operator / (BaseType scalar) const noexcept->Vector3;
		auto operator * (const Matrix44& mat) const noexcept->Vector3;
		friend auto operator *(const Matrix44& mat, const Vector3& vec) noexcept->Vector3;
		friend auto operator * (BaseType scalar, const Vector3& vec) noexcept->Vector3;

		// equality operators
		auto operator != (const Vector3& vec) const noexcept -> bool;
		auto operator ==(const Vector3& vec) const noexcept -> bool;

		// other methods
		auto GetLength() const noexcept->BaseType;
		auto GetSquareLength() const noexcept->BaseType;
		auto GetNormalized() const noexcept->Vector3;
		auto Normalize() noexcept->BaseType;
		auto Dot(const Vector3& vec) const noexcept->BaseType;
		auto Cross(const Vector3& vec) const noexcept->Vector3;

		// static constants
		static Vector3 One;
		static Vector3 Zero;

		// members
		BaseType x, y, z;
	};

	auto operator * (Vector3::BaseType scalar, const Vector3& vec) noexcept->Vector3;
	auto operator * (const Matrix44& mat, const Vector3& vec) noexcept->Vector3;

	//------------------------------------------------------
	// cast operators
	// --------------------------------------------------------------------------------
	Vector3::operator BaseType* () noexcept
	{
		return &x;
	}

	// --------------------------------------------------------------------------------
	Vector3::operator const BaseType* () const noexcept
	{
		return &x;
	}
}