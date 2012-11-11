
#ifndef __OAK3D_INCLUDE_LEAF3D_SCREENRECTANGLE_H__
#define __OAK3D_INCLUDE_LEAF3D_SCREENRECTANGLE_H__

#include "ScreenPosition.h"
#include "ScreenSize2D.h"

namespace ro3d
{
	namespace Leaf3D
	{
		struct ScreenRectangle
		{
			ScreenRectangle(int32_t x = 0, int32_t y = 0, uint32_t width = 0, uint32_t height = 0) : m_pos(x, y), m_size(width, height) {}
			ScreenRectangle(const ScreenPosition2D &pos, const ScreenSize2D &size) : m_pos(pos), m_size(size) {}

			ScreenPosition2D m_pos;
			ScreenSize2D m_size;
		};
	}
}

#endif
