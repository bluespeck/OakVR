#pragma once

#include <cstdint>

#define PI 3.14159265358979f
#define DEG2RAD(deg) ((180 / PI) * (deg))
#define RAD2DEG(rad) ((PI / 180) * (rad))

namespace oakvr
{
	namespace math
	{
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