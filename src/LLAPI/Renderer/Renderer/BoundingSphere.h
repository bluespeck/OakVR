#pragma once

#include "Math/Vector3.h"

namespace oakvr
{
	struct BoundingSphere
	{
		oakvr::math::Vector3 m_position;
		float m_radius;
	};
}