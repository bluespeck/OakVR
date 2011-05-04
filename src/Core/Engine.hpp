
namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		inline void Engine::SetGraphicsEngine(GraphicsEngine *pGE)
		{
			m_pGE = pGE;
		}

		// --------------------------------------------------------------------------------
		inline void Engine::SetRenderWindow(RenderWindow *pRW)
		{
			m_pRW = pRW;
		}

		inline void Engine::SetTimer(Timer *pTimer)
		{
			m_pTimer = pTimer;
		}
	}	// namespace Core
}	// namespace Oak3D