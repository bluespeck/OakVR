#pragma once

#include "Math/Vector3.h"


namespace oakvr
{
	namespace render
	{
		class BoundingSphere
		{
		public:
			auto IntersectsFrustum() -> bool;

			oakvr::math::Vector3 m_position;
			float m_radius;
		};
	}
}