
#ifndef __OAK3D_INCLUDE_LEAF3D_SCREENPOSITION_H__
#define __OAK3D_INCLUDE_LEAF3D_SCREENPOSITION_H__

#include <cstdint>

namespace ro3d
{
	namespace Leaf3D
	{
		struct ScreenPosition2D
		{
			ScreenPosition2D(int32_t x = 0, int32_t y = 0) : x(x), y(y) { }
			int32_t x, y;
		};
	}
}

#endif
