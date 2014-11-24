#pragma once

#include "Utils/Types.h"
#include "Mesh.h"
#include "Math/Matrix.h"

namespace oakvr
{
	namespace render
	{
		class Renderable
		{
		public:
			Renderable(const sp<Mesh> &pMesh = nullptr);

			void SetMesh(const sp<Mesh> &pMesh);
			auto GetMesh() const -> const sp<Mesh> &;

			void SetTransform(const oakvr::math::Matrix &transform);
			auto GetTransform() const -> const oakvr::math::Matrix &;
			void Transform(const oakvr::math::Matrix &transform);

		private:
			sp<Mesh> m_mesh;
			oakvr::math::Matrix m_transform;
		};
	}
}