
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_ENGINE_H__
#define __OAK3D_INCLUDE_ENGINE_H__

#include "Core/Utils/Singleton.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Renderer/IRenderer/GraphicsEngine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Core/Time/Timer.h"
#include "Leaf3D/Button.h"
#include "Renderer/IRenderer/Mesh.h"

namespace Oak3D
{
	class Engine : public Core::Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

		void Initialize();
		void Update();
			
		static void SetTimer(Core::Timer *pTimer);
		static void SetGraphicsEngine(Render::GraphicsEngine *pGE);
		static void SetRenderWindow(Render::RenderWindow *pRW);
		static void SetResourceManager(Core::ResourceManager *pRM);

		static Render::GraphicsEngine *GetGraphicsEngine();
		static Core::ResourceManager *GetResourceManager();
		static Render::RenderWindow *GetRenderWindow();
		static Core::Timer *GetTimer();
		static bool IsInitialized();

		
	private:			
		void Update(float dt);

		void TriggerInputEvents();
		void DrawInterface();
		void DrawMeshes();
		void DrawDebugText();
		void DrawAxes();
		void DrawMeshBoundingBoxes();

	private:
		Render::GraphicsEngine *m_pGE;
		Render::RenderWindow *m_pRW;
		Core::Timer *m_pTimer;
		Core::ResourceManager *m_pRM;

		bool m_bIsInitialized;

		// TODO These were added for testing only! Please remove them!
		Oak3D::Leaf3D::Button b1;
		Oak3D::Leaf3D::Button b2;
		Oak3D::Leaf3D::Button b3;
		Oak3D::Leaf3D::Button b4;
		Oak3D::Leaf3D::Button b5;

		Oak3D::Render::Mesh *pm1;
	};
}	// namespace Oak3D

#endif
