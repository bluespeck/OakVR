
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

namespace Oak3D
{
	namespace Math
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

		//------------------------------------------------------
		// other methods

		float Vector2::Length() const
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
