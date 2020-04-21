
#include "Vector4.h"
#include <cmath>

namespace oakvr::math
{
	// --------------------------------------------------------------------------------
	Vector4::Vector4(const BaseType* arr) noexcept
	{
		x = arr[0];
		y = arr[1];
		z = arr[2];
		w = arr[3];
	}

	Vector4::Vector4(const std::initializer_list<BaseType>& initList) noexcept
	{
		BaseType* p = &x;
		for (size_t i = 0; i < initList.size() && i < 4; ++i)
			*(p++) = *(initList.begin() + i);
		for (size_t i = initList.size(); i < 4; ++i)
			*(p++) = 0.0f;
	}

	// --------------------------------------------------------------------------------
	// cast operators
	// --------------------------------------------------------------------------------
	Vector4::operator BaseType* () noexcept
	{
		return &x;
	}

	// --------------------------------------------------------------------------------
	Vector4::operator const BaseType* () const noexcept
	{
		return &x;
	}

	// --------------------------------------------------------------------------------
	// other methods
	// --------------------------------------------------------------------------------
	auto Vector4::GetLength() const noexcept -> BaseType
	{
		return std::pow(x * x + y * y + z * z + w * w, 0.5f);
	}

	// --------------------------------------------------------------------------------
	auto Vector4::GetSquareLength() const noexcept -> BaseType
	{
		return x * x + y * y + z * z + w * w;
	}

	// --------------------------------------------------------------------------------
	auto Vector4::Normalize() const noexcept -> Vector4
	{
		const BaseType magnitudeSquare = x * x + y * y + z * z;

		if (magnitudeSquare < 1e-15f)
			return Vector4(0.0f, 0.0f, 0.0f, 0.0f);

		const BaseType invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
		return Vector4(x * invDenom, y * invDenom, z * invDenom, w * invDenom);
	}

	// --------------------------------------------------------------------------------
	auto Vector4::Dot(const Vector4& vec) const noexcept -> BaseType
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	// static member initialization
	Vector4 Vector4::One = { 1.0f, 1.0f, 1.0f, 1.0f };
	Vector4 Vector4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };

}