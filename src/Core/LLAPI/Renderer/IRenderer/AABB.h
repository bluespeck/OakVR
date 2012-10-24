
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_RENDER_INCLUDE_AABB_H__
#define __OAK3D_RENDER_INCLUDE_AABB_H__

#include "Vector3.h"

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

#endif
