
#include <cmath>

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"


namespace oakvr
{
	namespace math
	{
		// --------------------------------------------------------------------------------
		Vector3::Vector3(float x, float y, float z) :x(x), y(y), z(z)
		{
		}

		Vector3::Vector3(const std::initializer_list<float> &initList)
		{
			float *p = &x;
			for (size_t i = 0; i < initList.size() && i < 3; ++i)
				*(p++) = *(initList.begin() + i);
		}

		// --------------------------------------------------------------------------------
		Vector3::Vector3(const Vector4 &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		// --------------------------------------------------------------------------------
		Vector3::Vector3(const float* arr)
		{
			x = arr[0];
			y = arr[1];
			z = arr[2];
		}
		
		//------------------------------------------------------
		// other methods
		// --------------------------------------------------------------------------------
		float Vector3::GetLength() const
		{
			return std::pow(x * x + y * y + z * z, 0.5f);
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::GetNormalized() const
		{
			const float magnitudeSquare = x * x + y * y + z * z;

			if (magnitudeSquare < 1e-15f)
				return Vector3(0.0f, 0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector3(x * invDenom, y * invDenom, z * invDenom);
		}

		// --------------------------------------------------------------------------------
		float Vector3::Normalize()
		{
			const float magnitudeSquare = x * x + y * y + z * z;

			if (magnitudeSquare < 1e-15f)
				return 0.0f;

			float length = std::pow(magnitudeSquare, 0.5f);
			const float invDenom = 1.0f / length;
			x *= invDenom;
			y *= invDenom;
			z *= invDenom;
			return length;
		}

		// --------------------------------------------------------------------------------
		float Vector3::Dot(const Vector3 &vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::Cross(const Vector3 &vec) const
		{
			// compute as 3D cross product
			return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);

		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator * (const Matrix &mat) const
		{
			Vector3 result;
			result.x = x * mat._11 + y * mat._21 + z * mat._31 + mat._41;
			result.y = x * mat._12 + y * mat._22 + z * mat._32 + mat._42;
			result.z = x * mat._13 + y * mat._23 + z * mat._33 + mat._43;
			return result;
		}

		// --------------------------------------------------------------------------------
		Vector3 operator * (const Matrix &mat, const Vector3 &vec)
		{
			Vector3 result;
			result.x = vec.x * mat._11 + vec.y * mat._12 + vec.z * mat._13 + mat._14;
			result.y = vec.x * mat._21 + vec.y * mat._22 + vec.z * mat._23 + mat._24;
			result.z = vec.x * mat._31 + vec.y * mat._32 + vec.z * mat._33 + mat._34;
			return result;
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator * (float scalar) const
		{
			return Vector3(scalar * x, scalar * y, scalar * z);
		}

		// --------------------------------------------------------------------------------
		Vector3 operator * (float scalar, const Vector3 &vec)
		{
			return Vector3(scalar * vec.x, scalar * vec.y, scalar * vec.z);
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator / (float scalar) const
		{
			float invDenom = 1 / scalar;
			return Vector3(x * invDenom, y * invDenom, z * invDenom);
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator + () const
		{
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator + (const Vector3 &vec) const
		{
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}

		// --------------------------------------------------------------------------------
		Vector3 Vector3::operator - (const Vector3 &vec) const
		{
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}

		// --------------------------------------------------------------------------------
		Vector3& Vector3::operator += (const Vector3 &vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector3& Vector3::operator -= (const Vector3 &vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector3& Vector3::operator *= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		// --------------------------------------------------------------------------------
		Vector3& Vector3::operator /= (float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

	}	// namespace Math
}	// namespace oakvr
