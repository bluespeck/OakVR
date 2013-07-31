#pragma once

#include "Math/Vector3.h"

namespace oakvr
{
	namespace Render
	{

		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			oakvr::Math::Vector3 m_vecLeftBottomFront;
			oakvr::Math::Vector3 m_vecRightTopBack;
		};

	} // namespace Render
} // namespace oakvr
