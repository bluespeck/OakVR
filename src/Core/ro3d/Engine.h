#pragma once

#include "Utils/Singleton.h"
#include "ResourceManager/ResourceManager.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Time/Timer.h"
//#include "Leaf3D/Button.h"
#include "Renderer/IRenderer/Mesh.h"
#include "CameraManager.h"

namespace ro3d
{
	class Engine : public ro3d::Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

		void Initialize();
		void Update();
			
		static void SetTimer(Core::Timer *pTimer);
		static void SetRenderer(Render::IRenderer *pGE);
		static void SetRenderWindow(Render::RenderWindow *pRW);
		static void SetResourceManager(Core::ResourceManager *pRM);

		static Render::IRenderer *GetRenderer();
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
		Render::IRenderer *m_pGE;
		Render::RenderWindow *m_pRW;
		Render::CameraManager *m_pCM;
		Core::Timer *m_pTimer;
		Core::ResourceManager *m_pRM;

		bool m_bIsInitialized;
	};
}	// namespace ro3d

