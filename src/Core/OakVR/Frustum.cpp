#include "Frustum.h"

namespace oakvr
{
	bool Frustum::Intersects(const math::Vector3 &point)
	{
		for (int i = 0; i < 6; ++i)
			if (m_planes[i].SignedDistance(point) < 0)
				return false;
		return true;
	}

	bool Frustum::Intersects(const math::Vector3 &point, float radius)
	{
		for (int i = 0; i < 6; ++i)
		{
			float dist = m_planes[i].SignedDistance(point);
			if (dist < -radius)
				return false;
			else if (dist < radius)
				return true;
		}
		return true;
	}
}