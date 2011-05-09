
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_AABB_H__
#define __OAK3D_INCLUDE_AABB_H__

#include "../Math/Vector3.h"

namespace Oak3D
{
	namespace Utils
	{

		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			Oak3D::Math::Vector3 m_vecLeftBottomFront;
			Oak3D::Math::Vector3 m_vecRightTopBack;
		};

	} // namespace Utils
}

#endif
