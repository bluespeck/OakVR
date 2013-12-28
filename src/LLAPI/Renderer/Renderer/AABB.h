#pragma once

#include "Math/Vector3.h"

namespace oakvr
{
	namespace render
	{

		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			oakvr::math::Vector3 m_vecLeftBottomFront;
			oakvr::math::Vector3 m_vecRightTopBack;
		};

	} // namespace render
} // namespace oakvr
