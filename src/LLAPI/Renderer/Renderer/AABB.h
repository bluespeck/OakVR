#pragma once

#include "Math/Vector3.h"

namespace oakvr
{
	struct AABB
	{
		oakvr::math::Vector3 m_vecLeftBottomFront = { 0.f, 0.f, 0.f };
		oakvr::math::Vector3 m_vecRightTopBack = { 0.f, 0.f, 0.f };
	};
} // namespace oakvr
