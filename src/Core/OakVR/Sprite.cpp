#include "Sprite.h"
#include "Utils/RenderUtils.h"
#include "Utils/Buffer.h"
#include "Interface.h"

namespace oakvr
{
	namespace render
	{
		Sprite::Sprite(const std::string &name, const oakvr::math::Vector3 &center, float width, float height, const std::string &textureName)
			: m_name( name ), m_center( center ), m_width{ width }, m_height{ height }, m_textureName( textureName )
		{
			std::vector<oakvr::render::VertexElementDescriptor> ved{
				oakvr::render::VertexElementDescriptor::Semantic::position,
				oakvr::render::VertexElementDescriptor::Semantic::tex_coord,
			};

			oakvr::core::MemoryBuffer vb{ 4 * ComputeVertexStride(ved) * sizeof(float) };
			oakvr::core::MemoryBuffer ib{ 2 * 3 * sizeof(uint32_t) };

			float pVertices[] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				+0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				+0.5f, +0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f, +0.5f, 0.0f, 0.0f, 1.0f,

			};

			uint32_t pIndices[] = {
				0, 1, 2,
				0, 2, 3,
			};

			memcpy(vb.GetDataPtr(), pVertices, vb.Size());
			memcpy(ib.GetDataPtr(), pIndices, ib.Size());

			auto pMaterial = std::make_shared<oakvr::render::Material>("Default");

			m_pMesh = oakvr::render::CreateMesh(m_name, ved, vb, 4, ib, pMaterial, { m_textureName });
			auto scaleMatrix = oakvr::math::Matrix::Scale(width, height, 1.0f);
			auto translationMatrix = oakvr::math::Matrix::Translation(m_center);
			m_pMesh->SetWorldMatrix(translationMatrix * scaleMatrix);

		}

		auto Sprite::SetCenterPosition(const oakvr::math::Vector3 &vec) -> void
		{
			m_center = vec;
			auto pMesh = oakvr::render::GetMesh(m_name);
			auto scaleMatrix = oakvr::math::Matrix::Scale(m_width, m_height, 1.0f);
			auto translationMatrix = oakvr::math::Matrix::Translation(m_center);
			m_pMesh->SetWorldMatrix(translationMatrix * scaleMatrix);
		}

		auto Sprite::SetScaleFactor(float newScaleFactor) -> void
		{
			m_scaleFactor = newScaleFactor;
			auto pMesh = oakvr::render::GetMesh(m_name);
			auto scaleMatrix = oakvr::math::Matrix::Scale(m_width * m_scaleFactor, m_height * m_scaleFactor, 1.0f);
			auto translationMatrix = oakvr::math::Matrix::Translation(m_center);
			m_pMesh->SetWorldMatrix(translationMatrix * scaleMatrix);
		}

		Sprite::~Sprite()
		{
			oakvr::render::RemoveMesh(m_name);
		}
	}
}