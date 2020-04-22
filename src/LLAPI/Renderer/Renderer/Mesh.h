#pragma once

#include "Utils/StringId.h"
#include "MeshElement.h"
#include "Math/Matrix44.h"
#include "BoundingSphere.h"

#include <memory>
#include <vector>
#include <cstdint>

using namespace std::string_literals;

namespace oakvr::render
{
	class Mesh
	{
	public:
		typedef std::vector<MeshElementSharedPointer> MeshElementVector;

		Mesh(const StringId& name = ""s);
		~Mesh();

		inline auto AddMeshElement(const sp<MeshElement>& meshElem) -> void;
		inline auto GetMeshElements()->MeshElementVector&;
		inline auto GetMeshElements() const -> const MeshElementVector&;
		inline auto SetWorldMatrix(const oakvr::math::Matrix44& worldMatrix) -> void;
		inline auto GetWorldMatrix() const -> const oakvr::math::Matrix44&;
		inline auto Transform(const oakvr::math::Matrix44& transform) -> void;

		inline auto GetBoundingSphere() const noexcept -> const BoundingSphere&;

		inline auto GetName() const -> const StringId&;

	private:
		StringId m_name;
		MeshElementVector m_vMeshElements;
		oakvr::math::Matrix44 m_worldMatrix;

		BoundingSphere m_boundingSphere;

	};

	using MeshSharedPointer = sp < Mesh >;

	auto Mesh::AddMeshElement(const sp<MeshElement>& pMeshElem) -> void
	{
		pMeshElem->m_pMesh = this;
		m_vMeshElements.push_back(pMeshElem);

		const auto& c1 = m_boundingSphere.m_position;
		const auto& c2 = pMeshElem->m_boundingSphere.m_position;
		const auto& r1 = m_boundingSphere.m_radius;
		const auto& r2 = pMeshElem->m_boundingSphere.m_radius;

		auto deltaR = c2 - c1;
		auto c11 = c1 + r1 * deltaR.GetNormalized();
		auto c22 = c2 - r2 * deltaR.GetNormalized();
		m_boundingSphere.m_position = c11 - (c11 - c22) / 2;
		m_boundingSphere.m_radius = (r1 + r2) - abs(r1 - r2) / 2;
	}

	auto Mesh::GetMeshElements() -> MeshElementVector&
	{
		return m_vMeshElements;
	}

	auto Mesh::GetMeshElements() const -> const MeshElementVector&
	{
		return m_vMeshElements;
	}

	auto Mesh::SetWorldMatrix(const oakvr::math::Matrix44& worldMatrix) -> void
	{
		m_worldMatrix = worldMatrix;
	}

	auto Mesh::GetWorldMatrix() const -> const oakvr::math::Matrix44&
	{
		return m_worldMatrix;
	}

	auto Mesh::Transform(const oakvr::math::Matrix44& transform) -> void
	{
		m_worldMatrix = transform * m_worldMatrix;
	}

	auto Mesh::GetBoundingSphere() const noexcept -> const BoundingSphere&
	{
		return m_boundingSphere;
	}

	auto Mesh::GetName() const -> const StringId&
	{
		return m_name;
	}
}

