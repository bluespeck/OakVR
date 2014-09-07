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
			typedef std::vector<std::shared_ptr<MeshElement>> MeshElementVector;

			Mesh(const std::string &name = "");
			~Mesh();

			void AddMeshElement(const std::shared_ptr<MeshElement> &meshElem);
			auto GetMeshElements() -> MeshElementVector & { return m_vMeshElements; }
			auto GetMeshElements() const -> const MeshElementVector &{ return m_vMeshElements; }
			void SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) { m_worldMatrix = worldMatrix; }
			auto GetWorldMatrix() const -> const oakvr::math::Matrix & { return m_worldMatrix; }
			void Transform(const oakvr::math::Matrix &transform) { m_worldMatrix = transform * m_worldMatrix; }

			auto GetName() const -> const std::string & { return m_name; }

		private:
			std::string m_name;
			MeshElementVector m_vMeshElements;
			oakvr::math::Matrix m_worldMatrix;

		};

	} // namespace render
} // namespace oakvr

