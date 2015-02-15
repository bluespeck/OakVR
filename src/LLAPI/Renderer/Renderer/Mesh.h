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

			void AddMeshElement(const sp<MeshElement> &meshElem);
			auto GetMeshElements() -> MeshElementVector & { return m_vMeshElements; }
			auto GetMeshElements() const -> const MeshElementVector &{ return m_vMeshElements; }
			void SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) { m_worldMatrix = worldMatrix; }
			auto GetWorldMatrix() const -> const oakvr::math::Matrix & { return m_worldMatrix; }
			void Transform(const oakvr::math::Matrix &transform) { m_worldMatrix = transform * m_worldMatrix; }

			auto GetName() const -> const StringId & { return m_name; }

		private:
			StringId m_name;
			MeshElementVector m_vMeshElements;
			oakvr::math::Matrix m_worldMatrix;

		};

		using MeshSharedPointer = sp < Mesh > ;

	} // namespace render
} // namespace oakvr

