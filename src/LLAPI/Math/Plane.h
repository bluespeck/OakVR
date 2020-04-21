#pragma once

#include "Vector3.h"

namespace oakvr::math
{
	class Plane
	{
	public:
		auto Distance(const Vector3& point) const -> float;
		auto SignedDistance(const Vector3& point) const -> float;

		Vector3 normal;
		float w;
	};
}