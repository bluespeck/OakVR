
#ifndef __OAK3D_INCLUDE_LEAF3D_SCREENSIZE2D_H__
#define __OAK3D_INCLUDE_LEAF3D_SCREENSIZE2D_H__

#include <cstdint>

namespace Oak3D
{
	namespace Leaf3D
	{
		struct ScreenSize2D
		{
			ScreenSize2D(uint32_t width = 0, uint32_t height = 0) : width(width), height(height) { }
			uint32_t width, height;
		};
	}
}

#endif
