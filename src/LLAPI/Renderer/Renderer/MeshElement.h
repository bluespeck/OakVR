#pragma once

#include <memory>
#include <vector>

#include "Utils\Buffer.h"

namespace oakvr
{
	namespace render
	{
		struct VertexElementDescriptor
		{			
			uint8_t size;
			enum class Semantic
			{
				position,
				tex_coord,
				normal,
			} semantic;
		};
		
		class Material;

		class MeshElement
		{
		public:
			MeshElement(const VertexElementDescriptor &vertexFormat, const oakvr::core::MemoryBuffer &vb
				, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
				, std::shared_ptr<Material> &pMaterial);
			MeshElement(const std::vector<VertexElementDescriptor> &vertexFormat, const oakvr::core::MemoryBuffer &vb
						, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
						, std::shared_ptr<Material> &pMaterial);
			~MeshElement();

			oakvr::core::MemoryBuffer m_vertexData;
			oakvr::core::MemoryBuffer m_indexData;
			std::vector<VertexElementDescriptor> m_vertexFormat;
			uint8_t m_vertexStride;
			uint8_t m_indexStride;

			std::shared_ptr<Material> m_pMaterial;
		};
	}
}
