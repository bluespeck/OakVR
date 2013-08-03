
#ifndef __OAKVR_INCLUDE_LEAF3D_FOCUSZONE_H__
#define __OAKVR_INCLUDE_LEAF3D_FOCUSZONE_H__

#include "ScreenRectangle.h"

namespace oakvr
{
	namespace Leaf3D
	{
		struct FocusZone
		{
			FocusZone(int32_t x = 0, int32_t y = 0, uint32_t width = 0, uint32_t height = 0, uint32_t depth = 0) : m_focusRect(x, y, width, height), m_focusDepth(depth) { }
			FocusZone(const ScreenPosition2D &pos, const ScreenSize2D &size, uint32_t depth) : m_focusRect(pos, size), m_focusDepth(depth) { }
			FocusZone(const ScreenRectangle &rectangle, uint32_t depth) : m_focusRect(rectangle), m_focusDepth(depth) { }

			ScreenRectangle m_focusRect;
			uint32_t m_focusDepth;
		};
	}
}

#endif
