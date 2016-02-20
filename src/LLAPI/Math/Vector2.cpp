
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

namespace oakvr
{
	namespace math
	{
		Vector2::Vector2(float x, float y):x(x), y(y)
		{
		}

		Vector2::Vector2(const Vector3 &vec)
		{ 
			x = vec.x;
			y = vec.y;
		}

		Vector2::Vector2(const float* arr)
		{ 
			x = arr[0];
			y = arr[1];
		}

		Vector2::Vector2(const std::pair<float, float> &coords)
		{
			x = coords.first;
			y = coords.second;
		}

		Vector2::Vector2(const std::initializer_list<float> &initList)
		{
			float *p = &x;
			for (size_t i = 0; i < initList.size() && i < 2; ++i)
				*(p++) = *(initList.begin() + i);
			for (size_t i = initList.size(); i < 2; ++i)
				*(p++) = 0.0f;
		}

		//------------------------------------------------------
		// cast operators

		Vector2::operator float *()
		{
			return &x;
		}

		Vector2::operator const float *() const
		{
			return &x;
		}

		// arithmetic operators
		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator * (float scalar) const
		{
			return Vector2(scalar * x, scalar * y);
		}

		// --------------------------------------------------------------------------------
		auto operator * (float scalar, const Vector2 &vec) -> Vector2
		{
			return Vector2(scalar * vec.x, scalar * vec.y);
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator / (float scalar) const
		{
			float invDenom = 1 / scalar;
			return Vector2(x * invDenom, y * invDenom);
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator + () const
		{
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator - () const
		{
			return Vector2{-x, -y};
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator + (const Vector2 &vec) const
		{
			return Vector2{x + vec.x, y + vec.y};
		}

		// --------------------------------------------------------------------------------
		Vector2 Vector2::operator - (const Vector2 &vec) const
		{
			return Vector2{x - vec.x, y - vec.y};
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator += (const Vector2 &vec)
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator -= (const Vector2 &vec)
		{
			x -= vec.x;
			y -= vec.y;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator *= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector2& Vector2::operator /= (float scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		//------------------------------------------------------
		// other methods
		//------------------------------------------------------
		auto Vector2::GetLength() const -> float
		{ 
			return std::pow(x * x + y * y, 0.5f); 
		}

		//------------------------------------------------------
		auto Vector2::GetSquareLength() const -> float
		{
			return x * x + y * y;
		}
		
		auto Vector2::Normalize() const -> Vector2
		{
			const float magnitudeSquare = x * x + y * y;

			if(magnitudeSquare < 1e-15f)
				return Vector2(0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector2(x * invDenom, y * invDenom);
		}

		auto Vector2::Dot(const Vector2 &vec) const -> float
		{
			return x * vec.x + y * vec.y;
		}

		// static member initialization
		Vector2 Vector2::One =	{ 1.0f, 1.0f };
		Vector2 Vector2::Zero = { 0.0f, 0.0f };

		

	}// namespace Math
}
