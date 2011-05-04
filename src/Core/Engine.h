
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_ENGINE_H__
#define __OAK3D_INCLUDE_ENGINE_H__

namespace Oak3D
{
	namespace Core
	{
		class Timer;
		class GraphicsEngine;
		class RenderWindow;

		class Engine
		{
		public:
			Engine();
			~Engine();

			void Initialize();
			void Update();
			
			inline void SetTimer(Timer *pTimer);
			inline void SetGraphicsEngine(GraphicsEngine *pGE);
			inline void SetRenderWindow(RenderWindow *pRW);

		private:
			void Update(float dt);

		private:
			GraphicsEngine *m_pGE;
			RenderWindow *m_pRW;
			Timer *m_pTimer;
		};
	}	// namespace Core
}	// namespace Oak3D

#include "Engine.hpp"

#endif
