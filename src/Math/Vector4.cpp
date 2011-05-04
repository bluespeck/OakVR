
#include "Vector4.h"
#include <cmath>

namespace Oak3D
{
	namespace Math
	{
		Vector4::Vector4(float x, float y, float z, float w)
			:x(x), y(y), z(z), w(w)
		{
		}
		
		Vector4::Vector4(const float* arr)
		{ 
			x = arr[0];
			y = arr[1];
			z = arr[2];
			w = arr[3];
		}

		// --------------------------------------------------------------------------------
		// cast operators

		Vector4::operator float *()
		{
			return &x;
		}

		Vector4::operator const float *() const
		{
			return &x;
		}

		// --------------------------------------------------------------------------------
		// other methods

		float Vector4::Length() const
		{ 
			return std::pow(x * x + y * y, 0.5f); 
		}

		// --------------------------------------------------------------------------------
		Vector4 Vector4::Normalize() const
		{
			const float magnitudeSquare = x * x + y * y;

			if(magnitudeSquare < 1e-15f)
				return Vector4(0.0f, 0.0f, 0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector4(x * invDenom, y * invDenom, z * invDenom, w * invDenom);
		}

		// --------------------------------------------------------------------------------
		float Vector4::Dot(const Vector4 &vec) const
		{
			return x * vec.x + y * vec.y;
		}



	}// namespace Math
}
