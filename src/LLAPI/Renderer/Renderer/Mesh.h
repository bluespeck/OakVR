#pragma once

#include "MeshElement.h"
#include "Math/Matrix.h"

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
			Mesh(const std::string &name = "");
			~Mesh();

			void AddMeshElement(std::shared_ptr<MeshElement> &meshElem);
			std::vector<std::shared_ptr<MeshElement>> &GetMeshElements() { return m_vMeshElements; }
			const std::vector<std::shared_ptr<MeshElement>> &GetMeshElements() const { return m_vMeshElements; }
			void SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) { m_worldMatrix = worldMatrix; }
			const oakvr::math::Matrix & GetWorldMatrix() const { return m_worldMatrix; }

			const std::string &GetName() const { return m_name; }

		private:
			std::string m_name;
			std::vector<std::shared_ptr<MeshElement>> m_vMeshElements;
			oakvr::math::Matrix m_worldMatrix;

		};

	} // namespace render
} // namespace oakvr

