#pragma once

#include "Material.h"

#include <memory>

namespace oakvr
{
	namespace render
	{
		class MeshElement
		{

			MeshElement() = default;
			MeshElement(std::shared_ptr<Material> pMaterial);
		private:
			uint8_t *m_pVertexData;
			uint8_t *m_pIndexData;
			uint32_t m_vertexSize;
			uint32_t m_vertexCount;


			uint32_t m_vertexFormat;
			uint32_t m_indexCount;

			std::shared_ptr<Material> m_pMaterial;
		};
	}
}
