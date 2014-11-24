#include "Renderable.h"

namespace oakvr
{
	namespace render
	{
		Renderable::Renderable(const sp<Mesh> &pMesh /* = nullptr */)
			:m_mesh{pMesh}
		{
			
		}

		void Renderable::SetMesh(const sp<Mesh> &pMesh)
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

		void Renderable::SetTransform(const oakvr::math::Matrix &transform)
		{
			m_transform = transform;
		}

		void Renderable::Transform(const oakvr::math::Matrix &transform)
		{
			m_transform = transform * m_transform;
		}
	}
}