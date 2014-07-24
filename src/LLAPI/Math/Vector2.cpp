
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

		Vector2::Vector2(const std::initializer_list<float> &coords)
		{
			float *p = &x;
			for (size_t i = 0; i < coords.size() && i < 2; ++i)
				*(p++) = *(coords.begin() + i);
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
		Vector2 operator * (float scalar, const Vector2 &vec)
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

		float Vector2::GetLength() const
		{ 
			return std::pow(x * x + y * y, 0.5f); 
		}
		
		Vector2 Vector2::Normalize() const
		{
			const float magnitudeSquare = x * x + y * y;

			if(magnitudeSquare < 1e-15f)
				return Vector2(0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector2(x * invDenom, y * invDenom);
		}

		float Vector2::Dot(const Vector2 &vec) const
		{
			return x * vec.x + y * vec.y;
		}

		

	}// namespace Math
}
