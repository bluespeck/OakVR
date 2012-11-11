#pragma once

#include "Math/Vector3.h"

namespace ro3d
{
	namespace Render
	{

		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			ro3d::Math::Vector3 m_vecLeftBottomFront;
			ro3d::Math::Vector3 m_vecRightTopBack;
		};

	} // namespace Render
} // namespace ro3d
