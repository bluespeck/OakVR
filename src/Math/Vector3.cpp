
#include "Vector3.h"
#include "Vector4.h"
#include <cmath>

namespace Oak3D
{
	namespace Math
	{
		Vector3::Vector3(float x, float y, float z):x(x), y(y), z(z)
		{
		}

		Vector3::Vector3(const Vector4 &vec)
		{ 
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		Vector3::Vector3(const float* arr)
		{ 
			x = arr[0];
			y = arr[1];
			z = arr[2];
		}

		//------------------------------------------------------
		// cast operators

		Vector3::operator float *()
		{
			return &x;
		}

		Vector3::operator const float *() const
		{
			return &x;
		}

		//------------------------------------------------------
		// other methods

		float Vector3::Length() const
		{ 
			return std::pow(x * x + y * y + z * z, 0.5f); 
		}

		Vector3 Vector3::Normalize() const
		{
			const float magnitudeSquare = x * x + y * y + z * z;

			if(magnitudeSquare < 1e-15f)
				return Vector3(0.0f, 0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector3(x * invDenom, y * invDenom, z * invDenom);
		}

		float Vector3::Dot(const Vector3 &vec) const
		{
			return x * vec.x + y * vec.y;
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::Cross(const Vector3 &vec) const
		{
			// compute as 3D cross product
			return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);

		}




	}// namespace Math
}
