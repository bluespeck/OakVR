#pragma once

#include "Vector3.h"

namespace oakvr
{
	namespace math
	{
		class Plane
		{
		public:
			float Distance(const Vector3 &point) const;
			float SignedDistance(const Vector3 &point) const;

			Vector3 normal;
			float w;
		};
	}
}