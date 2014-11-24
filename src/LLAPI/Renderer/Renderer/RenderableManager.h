#pragma once

#include "Renderable.h"
#include "Utils/Types.h"

#include <vector>
#include <memory>


namespace oakvr
{
	namespace render
	{
		using RenderableVector = std::vector<sp<Renderable>>;

		class RenderableManager
		{
		public:
			
			RenderableManager();
			~RenderableManager();

			void AddRenderable(sp<Renderable> pRenderable);
			void AddOneFrameRenderable(sp<Renderable> pRenderable);
			void ClearOneFrameRenderables();
			void Clear();

			void RemoveRenderable(sp<Renderable> pRenderable);


			auto SortRenderablesByMaterial()->RenderableVector;
			auto SortRenderablesByCameraDistance(const oakvr::math::Vector3 &cameraPos, const oakvr::math::Vector3 &cameraForward)->RenderableVector;

			auto GetRenderables()->RenderableVector & { return m_renderables; }
			auto GetOneFrameRenderablees()->RenderableVector & { return m_oneFrameRenderables; }
		private:
			RenderableVector m_renderables;
			RenderableVector m_oneFrameRenderables;
		};
	}
}
