#pragma once

#include <vector>
#include <cstdint>

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

		struct VertexElementDescriptor
		{
			uint8_t size;
			enum class Semantic
			{
				position,
				tex_coord,
				normal,
				color
			} semantic;
		};

		inline uint32_t ComputeVertexStride(const std::vector<VertexElementDescriptor> &vertexElementDescriptors)
		{
			uint32_t stride = 0;
			for (auto &ved : vertexElementDescriptors)
				stride += ved.size;			
			return stride;
		}
	}	// namespace render
}	// namespace oakvr
