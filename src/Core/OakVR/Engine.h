#pragma once

#include "Utils/Singleton.h"
#include "ResourceManager/ResourceManager.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Time/Timer.h"
//#include "Leaf3D/Button.h"
#include "Renderer/IRenderer/Mesh.h"
#include "CameraManager.h"
#include "OakVR/UtilityTypes.h"

namespace oakvr
{
	class Engine : public oakvr::Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

		void Initialize();
		void Update();
			
		static void SetRenderer(Render::IRenderer *pGE);
		
		static Render::IRenderer *GetRenderer();
		static Core::ResourceManager *GetResourceManager();
		static const Timer &GetTimer() { return GetInstance().m_timer; }
		static bool IsInitialized();

		// render related interface
		static ScreenSize GetScreenSize();
		static WindowSize GetWindowSize();

	private:			
		void Update(double dt);

		void TriggerInputEvents();
		void DrawInterface();
		void DrawMeshes();
		void DrawDebugText();
		void DrawAxes();
		void DrawMeshBoundingBoxes();

	private:
		Timer m_timer;

		std::shared_ptr<oakvr::Render::IRenderer> m_pGE;
		std::shared_ptr<oakvr::Render::RenderWindow> m_pRW;
		std::shared_ptr<oakvr::Render::CameraManager> m_pCM;
		std::shared_ptr<oakvr::Core::ResourceManager> m_pRM;

		bool m_bIsInitialized;
	};
}	// namespace oakvr

