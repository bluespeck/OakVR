#pragma once

#include <vector>
#include <cstdint>

namespace oakvr
{
	namespace render
	{
		enum class PrimitiveTopology : uint32_t
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
			enum class Semantic : uint32_t
			{
				position,
				tex_coord,
				normal,
				color
			} semantic;
			uint8_t size;

			VertexElementDescriptor(Semantic _semantic)
				: semantic{_semantic}
			{
				switch (semantic)
				{
				case Semantic::position:	size = 12;	break;
				case Semantic::tex_coord:	size = 8;	break;
				case Semantic::normal:		size = 12;	break;
				case Semantic::color:		size = 16;	break;
				default: break;
				}
			}
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
