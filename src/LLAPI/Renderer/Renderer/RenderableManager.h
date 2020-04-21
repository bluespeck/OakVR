#pragma once

#include "Renderable.h"
#include "Utils/Types.h"

#include <vector>
#include <memory>


namespace oakvr::render
{
	using RenderableVector = std::vector<sp<Renderable>>;

	class RenderableManager
	{
	public:
			
		RenderableManager();
		~RenderableManager();

		auto AddRenderable(sp<Renderable> pRenderable) -> void;
		auto AddOneFrameRenderable(sp<Renderable> pRenderable) -> void;
		auto ClearOneFrameRenderables() -> void;
		auto Clear() -> void;

		auto RemoveRenderable(sp<Renderable> pRenderable) -> void;


		auto SortRenderablesByMaterial() -> RenderableVector;
		auto SortRenderablesByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward) -> RenderableVector;

		auto GetRenderables() -> RenderableVector & { return m_renderables; }
		auto GetOneFrameRenderablees() -> RenderableVector & { return m_oneFrameRenderables; }
	private:
		RenderableVector m_renderables;
		RenderableVector m_oneFrameRenderables;
	};
}
