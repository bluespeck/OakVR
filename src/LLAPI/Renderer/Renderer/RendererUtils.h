#pragma once

namespace oakvr
{
	namespace render
	{
		enum PrimitiveTopology
		{
			ePT_First = 0,
			ePT_PointList = ePT_First,
			ePT_LineList,
			ePT_LineStrip,
			ePT_TriangleList,
			ePT_TriangleStrip,
			ePT_Count
		};
	}	// namespace render
}	// namespace oakvr
