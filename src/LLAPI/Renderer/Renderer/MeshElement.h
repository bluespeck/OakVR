#pragma once

#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"
#include "BoundingSphere.h"

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

			using CountType = uint32_t;
			using StrideType = uint8_t;

			void SetMesh(Mesh* pMesh) noexcept { m_pMesh = pMesh; }
			auto GetMesh() const noexcept { return m_pMesh; }
			auto GetBoundingSphere() const noexcept -> const BoundingSphere & { return m_boundingSphere; }

			auto GetVertexData() const noexcept -> const oakvr::core::MemoryBuffer& { return m_vertexData; }
			auto GetVertexCount() const noexcept -> const CountType { return m_vertexCount; }
			auto GetVertexStride() const noexcept -> const StrideType { return m_vertexStride; }
			
			auto GetIndexData() const noexcept -> const oakvr::core::MemoryBuffer& { return m_indexData; }
			auto GetIndexCount() const noexcept -> const CountType { return m_indexCount; }
			auto GetIndexStride() const noexcept -> const StrideType { return m_indexStride; }

			auto GetVertexElementDescriptors() const noexcept -> const VertexElementDescriptorArray& { return m_vertexFormat; }

			auto GetMaterial() const noexcept -> const sp<Material> { return m_pMaterial; }

			auto GetTextureNames() const noexcept -> const std::vector<StringId>{ return m_vecTextures; }
			
		private:

			void ComputeBoundingSphere();

			Mesh *m_pMesh;
			oakvr::core::MemoryBuffer m_vertexData;
			oakvr::core::MemoryBuffer m_indexData;
			VertexElementDescriptorArray m_vertexFormat;
			sp<Material> m_pMaterial;
			std::vector<StringId> m_vecTextures;
			CountType m_vertexCount;
			CountType m_indexCount;
			StrideType m_vertexStride;
			StrideType m_indexStride;
			BoundingSphere m_boundingSphere;
		};

		using MeshElementSharedPointer = sp < MeshElement >;
	}
}
