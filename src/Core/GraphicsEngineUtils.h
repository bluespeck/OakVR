
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_GRAPHICSENGINEUTILS_H__
#define __OAK3D_INCLUDE_GRAPHICSENGINEUTILS_H__


namespace Oak3D
{
	namespace Core
	{
		enum ShaderType
		{
			eST_VertexShader,
			eST_PixelShader
		};

		enum PrimitiveTopology
		{
			ePT_PointList,
			ePT_LineList,
			ePT_LineStrip,
			ePT_TriangleList,
			ePT_TriangleStrip
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
