#pragma once
#include <memory>

#include "Time/Timer.h"
//#include "Leaf3D/Button.h"
#include "Renderer/Renderer/Mesh.h"
#include "OakVR/UtilityTypes.h"

namespace oakvr
{
	// forward declarations
	namespace render
	{
		class Renderer;
		class RenderWindow;
		class CameraManager;
	}
	namespace core
	{
		class ResourceManager;
	}

	// Engine class
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Update();
			

		// render related interface
		static ScreenSize GetScreenSize();
		static WindowSize GetWindowSize();
				
		void CleanUp();

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

		std::shared_ptr<oakvr::core::ResourceManager> m_pRM;
		std::shared_ptr<oakvr::render::RenderWindow> m_pRW;
		std::shared_ptr<oakvr::render::Renderer> m_pRenderer;
		std::shared_ptr<oakvr::render::CameraManager> m_pCM;
		

		bool m_bIsInitialized;
	};
}	// namespace oakvr

