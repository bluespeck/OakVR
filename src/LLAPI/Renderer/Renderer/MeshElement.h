#pragma once

#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"

#include <memory>
#include <vector>

namespace oakvr
{
	namespace render
	{
		class Material;
		class Texture;
		class Mesh;

		class MeshElement
		{
		public:
			MeshElement(const VertexElementDescriptor &vertexFormat, const oakvr::core::MemoryBuffer &vb
				, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
				, sp<Material> &pMaterial);
			MeshElement(const std::vector<VertexElementDescriptor> &vertexFormat, const oakvr::core::MemoryBuffer &vb
				, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
				, sp<Material> &pMaterial, const std::vector<StringId> &vecTextures);	// vecTextures elements coorespond to texcoord 0, 1, etc.
			~MeshElement();

			oakvr::core::MemoryBuffer m_vertexData;
			oakvr::core::MemoryBuffer m_indexData;
			std::vector<VertexElementDescriptor> m_vertexFormat;
			sp<Material> m_pMaterial;
			std::vector<StringId> m_vecTextures;
			uint32_t m_vertexCount;
			uint32_t m_indexCount;
			uint8_t m_vertexStride;			
			uint8_t m_indexStride;
			
		private:
			friend Mesh;
			friend class MeshManager;
			friend class Renderer;
			Mesh *m_pMesh;
		};
	}
}
