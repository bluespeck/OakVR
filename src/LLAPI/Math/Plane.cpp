#include "Plane.h"

#include <cmath>

namespace oakvr
{
	namespace math
	{
		auto Plane::Distance(const Vector3 &point) const -> float
		{
			return fabs(normal.x * point.x + normal.y * point.y + normal.z * point.z + w) / std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		}

		auto Plane::SignedDistance(const Vector3 &point) const -> float
		{
			return (normal.x * point.x + normal.y * point.y + normal.z * point.z + w) / std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		}
	}
}