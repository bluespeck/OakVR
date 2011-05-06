
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
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

		class Engine : public Utils::Singleton<Engine>
		{
		public:
			Engine();
			~Engine();

			void Initialize();
			void Update();
			
			void SetTimer(Timer *pTimer);
			void SetGraphicsEngine(GraphicsEngine *pGE);
			void SetRenderWindow(RenderWindow *pRW);

			inline GraphicsEngine *GetGraphicsEngine();

		private:
			void Update(float dt);

		private:
			GraphicsEngine *m_pGE;
			RenderWindow *m_pRW;
			Timer *m_pTimer;
		};

		// --------------------------------------------------------------------------------
		inline GraphicsEngine *Engine::GetGraphicsEngine()
		{
			return m_pGE;
		}

	}	// namespace Core
}	// namespace Oak3D

#endif
