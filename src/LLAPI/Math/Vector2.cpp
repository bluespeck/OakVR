
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

namespace oakvr
{
	namespace math
	{
		Vector2::Vector2(const BaseType* arr) noexcept
		{ 
			x = arr[0];
			y = arr[1];
		}

		Vector2::Vector2(const std::pair<BaseType, BaseType> &coords) noexcept
		{
			x = coords.first;
			y = coords.second;
		}

		Vector2::Vector2(const std::initializer_list<BaseType> &initList) noexcept
		{
			BaseType *p = &x;
			for (size_t i = 0; i < initList.size() && i < 2; ++i)
				*(p++) = *(initList.begin() + i);
			for (size_t i = initList.size(); i < 2; ++i)
				*(p++) = 0.0f;
		}

		Vector2::Vector2(const Vector3 &vec) noexcept
		{
			x = vec.x;
			y = vec.y;
		}

		//------------------------------------------------------
		// cast operators

		Vector2::operator BaseType *() noexcept
		{
			return &x;
		}

		Vector2::operator const BaseType *() const noexcept
		{
			return &x;
		}

		// arithmetic operators
		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator * (BaseType scalar) const noexcept
		{
			return Vector2(scalar * x, scalar * y);
		}

		// --------------------------------------------------------------------------------
		auto operator * (Vector2::BaseType scalar, const Vector2 &vec) noexcept -> Vector2
		{
			return Vector2(scalar * vec.x, scalar * vec.y);
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator / (BaseType scalar) const noexcept
		{
			BaseType invDenom = 1 / scalar;
			return Vector2(x * invDenom, y * invDenom);
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator + () const noexcept
		{
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator - () const noexcept
		{
			return Vector2{-x, -y};
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator + (const Vector2 &vec) const noexcept
		{
			return Vector2{x + vec.x, y + vec.y};
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator - (const Vector2 &vec) const noexcept
		{
			return Vector2{x - vec.x, y - vec.y};
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator += (const Vector2 &vec) noexcept
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator -= (const Vector2 &vec) noexcept
		{
			x -= vec.x;
			y -= vec.y;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator *= (BaseType scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator /= (BaseType scalar) noexcept
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		//------------------------------------------------------
		// other methods
		//------------------------------------------------------
		auto Vector2::GetLength() const noexcept -> BaseType
		{ 
			return std::pow(x * x + y * y, 0.5f); 
		}

		//------------------------------------------------------
		auto Vector2::GetSquareLength() const noexcept -> BaseType
		{
			return x * x + y * y;
		}
		
		auto Vector2::Normalize() const noexcept -> Vector2
		{
			const BaseType magnitudeSquare = x * x + y * y;

			if(magnitudeSquare < 1e-15f)
				return Vector2(0.0f, 0.0f);

			const BaseType invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector2(x * invDenom, y * invDenom);
		}

		auto Vector2::Dot(const Vector2 &vec) const noexcept -> BaseType
		{
			return x * vec.x + y * vec.y;
		}

		// static member initialization
		Vector2 Vector2::One =	{ 1.0f, 1.0f };
		Vector2 Vector2::Zero = { 0.0f, 0.0f };

		

	}// namespace Math
}
