
#ifndef __OAKVR_INCLUDE_LEAF3D_SCREENPOSITION_H__
#define __OAKVR_INCLUDE_LEAF3D_SCREENPOSITION_H__

#include <cstdint>

namespace oakvr
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
