
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_ENGINE_H__
#define __OAK3D_INCLUDE_ENGINE_H__

#include "Core/Utils/Singleton.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Renderer/IRenderer/GraphicsEngine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Core/Time/Timer.h"

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

	private:
		Render::GraphicsEngine *m_pGE;
		Render::RenderWindow *m_pRW;
		Core::Timer *m_pTimer;
		Core::ResourceManager *m_pRM;

		bool m_bIsInitialized;
	};
}	// namespace Oak3D

#endif
