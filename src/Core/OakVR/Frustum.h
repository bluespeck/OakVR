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

		static const uint8_t near = 0;
		static const uint8_t far = 1;
		static const uint8_t left = 2;
		static const uint8_t right = 3;
		static const uint8_t top = 4;
		static const uint8_t bottom = 5;
		std::array<math::Plane, 6> m_planes;
	};
}