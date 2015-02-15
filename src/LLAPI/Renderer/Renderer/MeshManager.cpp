#include "MeshManager.h"
#include "Mesh.h"

#include "Profiler/Profiler.h"

#include <algorithm>

namespace oakvr
{
	namespace render
	{
		MeshManager::MeshManager()
		{

		}

		MeshManager::~MeshManager()
		{

		}

		auto MeshManager::AddMesh(sp<Mesh> pMesh) -> void
		{
			m_meshes.push_back(pMesh);
		}

		auto MeshManager::Clear() -> void
		{
			m_meshes.clear();
		}

		auto MeshManager::AddOneFrameMesh(sp<Mesh> pMesh) -> void
		{
			m_oneFrameMeshes.push_back(pMesh);
		}

		auto MeshManager::ClearOneFrameMeshes() -> void
		{
			m_oneFrameMeshes.clear();
		}

		auto MeshManager::RemoveMesh(sp<Mesh> pMesh) -> void
		{
			auto itEnd = std::remove_if(std::begin(m_meshes), std::end(m_meshes), 
				[&pMesh](sp<Mesh> pElem){ return pElem == pMesh; });
			if (itEnd != std::end(m_meshes))
				m_meshes.erase(itEnd);
		}

		auto MeshManager::SortMeshesByMaterial()->Mesh::MeshElementVector
		{	
			PROFILER_FUNC_SCOPED_TIMER;

			Mesh::MeshElementVector sortedElements;
			for (auto &pMesh : m_meshes)
			{
				auto meshElements = pMesh->GetMeshElements();
				sortedElements.insert(std::end(sortedElements), std::begin(meshElements), std::end(meshElements));
			}

			for (auto &pMesh : m_oneFrameMeshes)
			{
				auto meshElements = pMesh->GetMeshElements();
				sortedElements.insert(std::end(sortedElements), std::begin(meshElements), std::end(meshElements));
			}

			std::sort(std::begin(sortedElements), std::end(sortedElements), [](const Mesh::MeshElementVector::value_type &left, const Mesh::MeshElementVector::value_type &right) {
				return left->m_pMaterial > right->m_pMaterial;
			});
			
			return sortedElements;
		}

		auto MeshManager::SortByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward)->Mesh::MeshElementVector
		{
			PROFILER_FUNC_SCOPED_TIMER;

			Mesh::MeshElementVector sortedElements;
			for (auto &pMesh : m_meshes)
			{
				auto meshElements = pMesh->GetMeshElements();
				sortedElements.insert(std::end(sortedElements), std::begin(meshElements), std::end(meshElements));
			}

			for (auto &pMesh : m_oneFrameMeshes)
			{
				auto meshElements = pMesh->GetMeshElements();
				sortedElements.insert(std::end(sortedElements), std::begin(meshElements), std::end(meshElements));
			}

			std::sort(std::begin(sortedElements), std::end(sortedElements), [&](const Mesh::MeshElementVector::value_type &left, const Mesh::MeshElementVector::value_type &right) {
				auto &matLeft = left->m_pMesh->GetWorldMatrix();
				auto &matRight = right->m_pMesh->GetWorldMatrix();
				float squareDistanceLeft = (matLeft._41 * cameraForward.x - cameraPos.x * cameraPos.x) +
					(matLeft._42 * cameraForward.y - cameraPos.y * cameraPos.y) +
					(matLeft._43 * cameraForward.z - cameraPos.z * cameraPos.z);
				float squareDistanceRight = (matRight._41 * cameraForward.x - cameraPos.x * cameraPos.x) +
					(matRight._42 * cameraForward.y - cameraPos.y * cameraPos.y) +
					(matRight._43 * cameraForward.z - cameraPos.z * cameraPos.z);
				return squareDistanceLeft > squareDistanceRight;
			});

			return sortedElements;
		}

		
	}
}