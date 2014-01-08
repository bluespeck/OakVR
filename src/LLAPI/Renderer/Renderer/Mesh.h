#pragma once

#include "MeshElement.h"

#include <memory>
#include <vector>
#include <cstdint>

namespace oakvr
{
	namespace render
	{
		class Mesh
		{
		public:
			Mesh();
			~Mesh();

			//void AddMeshElement()
			std::vector<std::shared_ptr<MeshElement>> &GetMeshElements() { return m_vMeshElements; }
			const std::vector<std::shared_ptr<MeshElement>> &GetMeshElements() const { return m_vMeshElements; }

		private:
			std::vector<std::shared_ptr<MeshElement>> m_vMeshElements;
		};

	} // namespace render
} // namespace oakvr

