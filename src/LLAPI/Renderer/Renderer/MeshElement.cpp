#include "MeshElement.h"

#include <algorithm>
#include <cmath>

namespace oakvr::render
{
	MeshElement::MeshElement(const VertexElementDescriptor &vertexFormat, const oakvr::core::MemoryBuffer &vb
		, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
		, sp<Material> &pMaterial)
		: m_vertexData{ vb }, m_indexStride{ indexStride }, m_indexData{ ib }, m_pMaterial{pMaterial}
	{
		m_vertexFormat.push_back(vertexFormat);
		m_vertexStride = vertexFormat.size;
		m_indexCount = static_cast<uint32_t>(m_indexData.Size() / m_indexStride);
		m_vertexCount = static_cast<uint32_t>(m_vertexData.Size() / m_vertexStride);

		ComputeBoundingSphere();
	}

	MeshElement::MeshElement(const std::vector<VertexElementDescriptor> &vertexFormat, const oakvr::core::MemoryBuffer &vb
		, uint8_t indexStride, const oakvr::core::MemoryBuffer ib
		, sp<Material> &pMaterial, const std::vector<StringId> &vecTextures)
		: m_vertexFormat( vertexFormat ), m_vertexData{ vb }, m_indexStride{ indexStride }, m_indexData{ ib }, m_pMaterial{ pMaterial }, m_vecTextures(vecTextures)
	{
		m_vertexStride = 0;
		for (auto &e : m_vertexFormat)
		{
			m_vertexStride += e.size;
		}
		m_indexCount = static_cast<uint32_t>(m_indexData.Size() / m_indexStride);
		m_vertexCount = static_cast<uint32_t>(m_vertexData.Size() / m_vertexStride);

		ComputeBoundingSphere();
	}

	void MeshElement::ComputeBoundingSphere()
	{
		uint8_t vertexOffset = 0;
		bool bPositionFound = false;
		for (auto it = std::begin(m_vertexFormat); it != std::end(m_vertexFormat); ++it)
		{
			if (it->semantic != VertexElementDescriptor::Semantic::position)
				vertexOffset += it->size;
			else
			{
				bPositionFound = true;
				break;
			}
		}

		if (bPositionFound)
		{
			auto vertexDataPtr = m_vertexData.GetDataPtr() + vertexOffset;


			m_boundingSphere.m_position = { 0.f, 0.f, 0.f };
			m_boundingSphere.m_radius = 0.f;


			// compute bounding sphere
			for (uint32_t i = 0; i < m_vertexCount; ++i)
			{
				auto vertexPosPtr = reinterpret_cast<float*>(vertexDataPtr);
				m_boundingSphere.m_position += {vertexPosPtr[0], vertexPosPtr[1], vertexPosPtr[2]};
				vertexDataPtr += m_vertexStride;
			}
			m_boundingSphere.m_position /= static_cast<float>(m_vertexCount);
			vertexDataPtr = m_vertexData.GetDataPtr() + vertexOffset;
			float maxSquareDist = 0.f;
			for (uint32_t i = 0; i < m_vertexCount; ++i)
			{
				auto vertexPosPtr = reinterpret_cast<float*>(vertexDataPtr);
				auto centerRelVertexPos = oakvr::math::Vector3{ vertexPosPtr[0], vertexPosPtr[1], vertexPosPtr[2] } - m_boundingSphere.m_position;
				auto squareCenterRelVertexDist = centerRelVertexPos.GetSquareLength();
				if (squareCenterRelVertexDist > maxSquareDist)
					maxSquareDist = squareCenterRelVertexDist;
				vertexDataPtr += m_vertexStride;
			}
			m_boundingSphere.m_radius = std::sqrt(maxSquareDist);
		}
	}

	MeshElement::~MeshElement()
	{

	}
}