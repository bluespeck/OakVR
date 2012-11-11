#pragma once

#include "Math/Vector3.h"

namespace Oak3D
{
	namespace Render
	{

		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			Oak3D::Math::Vector3 m_vecLeftBottomFront;
			Oak3D::Math::Vector3 m_vecRightTopBack;
		};

	} // namespace Render
} // namespace Oak3D
