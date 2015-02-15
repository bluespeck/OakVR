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
			Renderable(const MeshSharedPointer &pMesh = nullptr);

			auto SetMesh(const MeshSharedPointer &pMesh) -> void;
			auto GetMesh() const -> const MeshSharedPointer &;

			auto SetTransform(const oakvr::math::Matrix &transform) -> void;
			auto GetTransform() const -> const oakvr::math::Matrix &;
			auto Transform(const oakvr::math::Matrix &transform) -> void;

		private:
			MeshSharedPointer m_mesh;
			oakvr::math::Matrix m_transform;
		};
	}
}