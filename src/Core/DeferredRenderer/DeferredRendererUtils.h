#pragma once

#include <cstdint>
#include "Math/Matrix.h"
#include <utils/StringId.h>
#include <Utils/Buffer.h>

namespace oakvr
{
	enum class RenderCallType
	{
		unknown,
		beginObjectRender,
		endObjectRender,
		setVertexShader,
		setPixelShader,
		setColor,
		setTexture,
		addVertices
	};

	enum class VertexFormat
	{
		xyz = 12,
		xyz_nxyz = 24,
		xyz_nxyz_uv = 32,
		xyz_uv = 20
	};

	uint8_t GetVertexFormatStride(VertexFormat vertexFormat) { return static_cast<uint8_t>(vertexFormat); }

	class Texture;
	class VertexBuffer;
	class VertexShader;
	class PixelShader;
	

	using Color = uint32_t;

	struct RenderCall
	{
		RenderCallType type;
		union
		{
			VertexFormat vertexFormat;
			oakvr::core::MemoryBuffer* vertices;
			oakvr::StringId textureId;
			oakvr::StringId vsId;
			oakvr::StringId psId;
			Color color;
		};

		RenderCall(RenderCallType type = RenderCallType::unknown) : type{ type } {}
		RenderCall(const RenderCall& renderCall) { memcpy(this, &renderCall, sizeof(RenderCall)); }
		~RenderCall() {}

		RenderCall &operator=(const RenderCall& renderCall) { memcpy(this, &renderCall, sizeof(RenderCall)); return *this; }
	};
}