#pragma once

#include <cstdint>

namespace oakvr
{
	namespace math
	{
		const float Pi = 3.14159265358979f;
		const float PiOverTwo = Pi / 2.f;
		const float PiOverThree = Pi / 3.f;
		const float PiOverFour = Pi / 4.f;
		const float PiOverSix = Pi / 6.f;
		const float PiOverTwelve = Pi / 12.f;

		inline auto DegreesToRadians(float degrees) -> float { return 3.14159265358979f / 180.0f * degrees; }
		inline auto RadiansToDegrees(float radians) -> float { return 180.0f / 3.14159265358979f * radians; }


		inline uint32_t NextPowerOfTwo(uint32_t n)
		{
			--n;
			n |= n >> 1;   // Divide by 2^k for consecutive doublings of k up to 32,
			n |= n >> 2;   // and then or the results.
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			return n + 1;
		}
	}
}