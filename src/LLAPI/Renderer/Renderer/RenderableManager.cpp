#include "RenderableManager.h"

#include "Profiler/Profiler.h"

#include <algorithm>

namespace oakvr::render
{
	RenderableManager::RenderableManager()
	{

	}

	RenderableManager::~RenderableManager()
	{

	}

	auto RenderableManager::AddRenderable(sp<Renderable> pRenderable) -> void
	{
		m_renderables.push_back(pRenderable);
	}

	auto RenderableManager::Clear() -> void
	{
		m_renderables.clear();
	}

	auto RenderableManager::AddOneFrameRenderable(sp<Renderable> pRenderable) -> void
	{
		m_oneFrameRenderables.push_back(pRenderable);
	}

	auto RenderableManager::ClearOneFrameRenderables() -> void
	{
		m_oneFrameRenderables.clear();
	}

	auto RenderableManager::RemoveRenderable(sp<Renderable> pRenderable) -> void
	{
		m_renderables.erase(std::remove(std::begin(m_renderables), std::end(m_renderables), pRenderable), m_renderables.end());
	}

	auto RenderableManager::SortRenderablesByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward)->RenderableVector
	{
		PROFILER_FUNC_SCOPED_TIMER;

		auto sortedRenderables = m_renderables;
		sortedRenderables.insert(sortedRenderables.end(), m_oneFrameRenderables.begin(), m_oneFrameRenderables.end());

		std::sort(std::begin(sortedRenderables), std::end(sortedRenderables), [&](const RenderableVector::value_type &left, const RenderableVector::value_type &right) {
			auto &matLeft = left->GetTransform();
			auto &matRight = right->GetTransform();
			float squareDistanceLeft = (matLeft._41 * cameraForward.x - cameraPos.x * cameraPos.x) +
				(matLeft._42 * cameraForward.y - cameraPos.y * cameraPos.y) +
				(matLeft._43 * cameraForward.z - cameraPos.z * cameraPos.z);
			float squareDistanceRight = (matRight._41 * cameraForward.x - cameraPos.x * cameraPos.x) +
				(matRight._42 * cameraForward.y - cameraPos.y * cameraPos.y) +
				(matRight._43 * cameraForward.z - cameraPos.z * cameraPos.z);
			return squareDistanceLeft > squareDistanceRight;
		});

		return sortedRenderables;
	}
}