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

			inline auto AddMeshElement(const sp<MeshElement> &meshElem) -> void;
			inline auto GetMeshElements() -> MeshElementVector &;
			inline auto GetMeshElements() const -> const MeshElementVector &;
			inline auto SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) -> void;
			inline auto GetWorldMatrix() const -> const oakvr::math::Matrix &;
			inline auto Transform(const oakvr::math::Matrix &transform) -> void;

			inline auto GetName() const -> const StringId &;

		private:
			StringId m_name;
			MeshElementVector m_vMeshElements;
			oakvr::math::Matrix m_worldMatrix;

		};

		using MeshSharedPointer = sp < Mesh > ;

		auto Mesh::AddMeshElement(const sp<MeshElement> &pMeshElem) -> void
		{
			pMeshElem->m_pMesh = this;
			m_vMeshElements.push_back(pMeshElem);
		}

		auto Mesh::GetMeshElements() -> MeshElementVector &
		{
			return m_vMeshElements;
		}

		auto Mesh::GetMeshElements() const -> const MeshElementVector &
		{
			return m_vMeshElements;
		}

		auto Mesh::SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) -> void
		{
			m_worldMatrix = worldMatrix; 
		}

		auto Mesh::GetWorldMatrix() const -> const oakvr::math::Matrix &
		{
			return m_worldMatrix;
		}

		auto Mesh::Transform(const oakvr::math::Matrix &transform) -> void
		{
			m_worldMatrix = transform * m_worldMatrix;
		}

		auto Mesh::GetName() const -> const StringId &
		{
			return m_name;
		}

	} // namespace render
} // namespace oakvr

