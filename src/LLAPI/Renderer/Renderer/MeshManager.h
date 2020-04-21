#pragma once

#include "Mesh.h"

#include <vector>
#include <memory>


namespace oakvr::render
{
	class MeshManager
	{
	public:
		typedef std::vector<sp<Mesh>> MeshVector;

		MeshManager();
		~MeshManager();

		auto AddMesh(sp<Mesh> pMesh) -> void;
		auto AddOneFrameMesh(sp<Mesh> pMesh) -> void;
		auto ClearOneFrameMeshes() -> void;
		auto Clear() -> void;

		auto RemoveMesh(sp<Mesh> pMesh) -> void;

		auto SortMeshesByMaterial() -> Mesh::MeshElementVector;
		auto SortByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward) -> Mesh::MeshElementVector;

		auto GetMeshes() -> MeshVector & { return m_meshes; }
		auto GetOneFrameMeshes() -> MeshVector & { return m_oneFrameMeshes; }
	private:
		MeshVector m_meshes;
		MeshVector m_oneFrameMeshes;
	};
}
