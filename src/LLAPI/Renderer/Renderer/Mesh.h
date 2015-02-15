#pragma once

#include "MeshElement.h"
#include "Math/Matrix.h"
#include "Utils/StringId.h"

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
			typedef std::vector<MeshElementSharedPointer> MeshElementVector;

			Mesh(const StringId &name = "");
			~Mesh();

			auto AddMeshElement(const sp<MeshElement> &meshElem) -> void;
			auto GetMeshElements() -> MeshElementVector & { return m_vMeshElements; }
			auto GetMeshElements() const -> const MeshElementVector &{ return m_vMeshElements; }
			auto SetWorldMatrix(const oakvr::math::Matrix &worldMatrix)  -> void{ m_worldMatrix = worldMatrix; }
			auto GetWorldMatrix() const -> const oakvr::math::Matrix & { return m_worldMatrix; }
			auto Transform(const oakvr::math::Matrix &transform)  -> void{ m_worldMatrix = transform * m_worldMatrix; }

			auto GetName() const -> const StringId & { return m_name; }

		private:
			StringId m_name;
			MeshElementVector m_vMeshElements;
			oakvr::math::Matrix m_worldMatrix;

		};

		using MeshSharedPointer = sp < Mesh > ;

	} // namespace render
} // namespace oakvr

