
#include "Vector4.h"
#include <cmath>

namespace oakvr
{
	namespace math
	{
		// --------------------------------------------------------------------------------
		Vector4::Vector4(float x, float y, float z, float w)
			:x(x), y(y), z(z), w(w)
		{
		}
		
		// --------------------------------------------------------------------------------
		Vector4::Vector4(const float* arr)
		{ 
			x = arr[0];
			y = arr[1];
			z = arr[2];
			w = arr[3];
		}

		Vector4::Vector4(const std::initializer_list<float> &initList)
		{
			float *p = &x;
			for (size_t i = 0; i < initList.size() && i < 4; ++i)
				*(p++) = *(initList.begin() + i);
			for (size_t i = initList.size(); i < 4; ++i)
				*(p++) = 0.0f;
		}

		// --------------------------------------------------------------------------------
		// cast operators
		// --------------------------------------------------------------------------------
		Vector4::operator float *()
		{
			return &x;
		}

		// --------------------------------------------------------------------------------
		Vector4::operator const float *() const
		{
			return &x;
		}

		// --------------------------------------------------------------------------------
		// other methods
		// --------------------------------------------------------------------------------
		auto Vector4::GetLength() const -> float
		{ 
			return std::pow(x * x + y * y + z * z + w * w, 0.5f); 
		}

		// --------------------------------------------------------------------------------
		auto Vector4::GetSquareLength() const -> float
		{
			return x * x + y * y + z * z + w * w;
		}

		// --------------------------------------------------------------------------------
		auto Vector4::Normalize() const -> Vector4
		{
			const float magnitudeSquare = x * x + y * y + z * z;

			if(magnitudeSquare < 1e-15f)
				return Vector4(0.0f, 0.0f, 0.0f, 0.0f);

			const float invDenom = 1.0f / std::pow(magnitudeSquare, 0.5f);
			return Vector4(x * invDenom, y * invDenom, z * invDenom, w * invDenom);
		}

		// --------------------------------------------------------------------------------
		auto Vector4::Dot(const Vector4 &vec) const -> float
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}

		// static member initialization
		Vector4 Vector4::One =	{ 1.0f, 1.0f, 1.0f, 1.0f };
		Vector4 Vector4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };

	}// namespace Math
}
