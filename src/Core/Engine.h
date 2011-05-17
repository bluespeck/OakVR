
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_ENGINE_H__
#define __OAK3D_INCLUDE_ENGINE_H__

#include "../Utils/Singleton.h"

namespace Oak3D
{
	namespace Core
	{
		class Timer;
		class GraphicsEngine;
		class RenderWindow;
		class ThreadFactory;

		class Engine : public Utils::Singleton<Engine>
		{
		public:
			Engine();
			~Engine();

			void Initialize();
			void Update();
			
			static void SetTimer(Timer *pTimer);
			static void SetGraphicsEngine(GraphicsEngine *pGE);
			static void SetRenderWindow(RenderWindow *pRW);
			static void SetThreadFactory(ThreadFactory *pThreadFactory);

			static GraphicsEngine *GetGraphicsEngine();
			static ThreadFactory* GetThreadFactory();

		
		private:			
			void Update(float dt);

		private:
			GraphicsEngine *m_pGE;
			RenderWindow *m_pRW;
			Timer *m_pTimer;
			ThreadFactory *m_pThreadFactory;
		};
	
	}	// namespace Core
}	// namespace Oak3D

#endif
