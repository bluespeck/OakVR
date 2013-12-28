#pragma once

namespace oakvr
{
	namespace render
	{
		enum ShaderType
		{
			eST_First = 0,
			eST_VertexShader = eST_First,
			eST_PixelShader,
			eST_GeometryShader,
			eST_HullShader,
			eST_DomainShader,
			eST_Count
		};

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
