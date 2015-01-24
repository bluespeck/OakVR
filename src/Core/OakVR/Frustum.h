#pragma once

#include "Math/Vector3.h"
#include "Math/Plane.h"
#include <cstdint>

#include <array>

namespace oakvr
{
	class Frustum
	{
	public:
		bool Intersects(const math::Vector3 &point);
		bool Intersects(const math::Vector3 &point, float radius);

		static const uint8_t nearIndex = 0;
		static const uint8_t farIndex = 1;
		static const uint8_t leftIndex = 2;
		static const uint8_t rightIndex = 3;
		static const uint8_t topIndex = 4;
		static const uint8_t bottomIndex = 5;
		std::array<math::Plane, 6> m_planes;
	};
}