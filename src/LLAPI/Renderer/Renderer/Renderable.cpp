#include "Renderable.h"

namespace oakvr::render
{
	Renderable::Renderable(const sp<Mesh> &pMesh /* = nullptr */)
		:m_mesh{pMesh}
	{
			
	}

	auto Renderable::SetMesh(const sp<Mesh> &pMesh) -> void
	{
		m_mesh = pMesh;
	}

	auto Renderable::GetMesh() const -> const sp<Mesh> &
	{
		return m_mesh;
	}

	auto Renderable::GetTransform() const -> const oakvr::math::Matrix &
	{
		return m_transform;
	}

	auto Renderable::SetTransform(const oakvr::math::Matrix &transform) -> void
	{
		m_transform = transform;
	}

	auto Renderable::Transform(const oakvr::math::Matrix &transform) -> void
	{
		m_transform = transform * m_transform;
	}
}