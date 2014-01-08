#pragma once

#include "Utils/Singleton.h"
#include "ResourceManager/ResourceManager.h"
#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RenderWindow.h"
#include "Time/Timer.h"
//#include "Leaf3D/Button.h"
#include "Renderer/Renderer/Mesh.h"
#include "CameraManager.h"
#include "OakVR/UtilityTypes.h"

namespace oakvr
{
	class Engine : public oakvr::Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Update();
			

		// render related interface
		static ScreenSize GetScreenSize();
		static WindowSize GetWindowSize();

	private:			
		bool Update(double dt);

		void TriggerInputEvents();
		void DrawInterface();
		void DrawMeshes();
		void DrawDebugText();
		void DrawAxes();
		void DrawMeshBoundingBoxes();

	private:
		Timer m_timer;

		std::shared_ptr<oakvr::render::Renderer> m_pRenderer;
		std::shared_ptr<oakvr::render::RenderWindow> m_pRW;
		std::shared_ptr<oakvr::render::CameraManager> m_pCM;

		bool m_bIsInitialized;
	};
}	// namespace oakvr

