#include "Engine.h"
#include "RenderWindow.h"
#include "GraphicsEngine.h"
#include "Timer.h"

namespace Oak3D
{
	namespace Core
	{
		Engine::Engine()
		{
			m_pGE = nullptr;
			m_pRW = nullptr;
			m_pTimer = nullptr;
			m_pThreadFactory = nullptr;
		}

		// --------------------------------------------------------------------------------
		Engine::~Engine()
		{
			if(m_pGE)
			{				
				delete m_pGE;
			}
			if(m_pRW)
				delete m_pRW;
			if(m_pTimer)
				delete m_pTimer;
		}

		// --------------------------------------------------------------------------------
		void Engine::Initialize()
		{
			if(m_pGE && m_pRW)
			{
				m_pRW->Initialize();
				m_pGE->SetRenderWindow(m_pRW);
				m_pGE->Initialize();
			}

			if(m_pTimer)
			{
				m_pTimer->Reset();
			}
		}

		// --------------------------------------------------------------------------------
		void Engine::Update()
		{
			m_pTimer->Tick();
			Update(m_pTimer->GetDeltaTime());
		}

		// --------------------------------------------------------------------------------
		void Engine::Update(float dt)
		{
			if(m_pGE)
			{
				// update engine stuff

				// render scene
				m_pGE->Render();
			}
		}

		// --------------------------------------------------------------------------------
		void Engine::SetGraphicsEngine(GraphicsEngine *pGE)
		{
			if(m_pInstance->m_pGE)
				delete m_pInstance->m_pGE;
			m_pInstance->m_pGE = pGE;
		}

		// --------------------------------------------------------------------------------
		void Engine::SetRenderWindow(RenderWindow *pRW)
		{
			if(m_pInstance->m_pRW)
				delete m_pInstance->m_pRW;
			m_pInstance->m_pRW = pRW;
		}

		// --------------------------------------------------------------------------------
		void Engine::SetTimer(Timer *pTimer)
		{
			if(m_pInstance->m_pTimer)
				delete m_pInstance->m_pTimer;
			m_pInstance->m_pTimer = pTimer;
		}

		// --------------------------------------------------------------------------------
		void Engine::SetThreadFactory(ThreadFactory *pThreadFactory)
		{
			m_pInstance->m_pThreadFactory = pThreadFactory;
		}

		// --------------------------------------------------------------------------------
		ThreadFactory* Engine::GetThreadFactory()
		{
			return m_pInstance->m_pThreadFactory;
		}

		// --------------------------------------------------------------------------------
		GraphicsEngine *Engine::GetGraphicsEngine()
		{
			return m_pInstance->m_pGE;
		}

	}	// namespace Core
}	// namespace Oak3D
