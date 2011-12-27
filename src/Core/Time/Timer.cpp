

#include "Timer.h"
#include <ctime>

namespace Oak3D
{
	namespace Core
	{
		Timer::Timer(void)
			: m_secondsPerCount(0.0), m_dt(-1.0), m_baseTime(0), 
			m_pausedTime(0), m_currTime(0), m_bPaused(false)
		{
			m_secondsPerCount = 1.0 / CLOCKS_PER_SEC;
			Reset();
		}

		Timer::~Timer(void)
		{
		}

		void Timer::Tick()
		{
			if( m_bPaused )
			{
				m_dt = 0.0;
				return;
			}

			m_currTime = clock();

			// Time difference between current call and last call of Tick
			m_dt = (m_currTime - m_prevTime) * m_secondsPerCount;

			m_prevTime = m_currTime;

			if(m_dt < 0.0)
			{
				m_dt = 0.0;
			}
		}

		// Time elapsed since the timer was started (excluding the time it was paused)
		float Timer::GetElapsedTime()const
		{	
			if( m_bPaused )
			{
				return (float)((m_pauseTime - m_baseTime) * m_secondsPerCount);
			}
			else
			{
				return (float)(((m_currTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
			}
		}

		float Timer::GetDeltaTime()const
		{
			return (float)m_dt;
		}

		bool Timer::IsPaused()const
		{
			return m_bPaused;
		}

		void Timer::Reset()
		{			
			m_baseTime = clock();
			m_prevTime = m_baseTime;
			m_pauseTime = 0;
			m_bPaused  = false;
		}

		void Timer::Unpause()
		{			
			if( m_bPaused )
			{
				int64_t startTime = clock();
				m_pausedTime += (startTime - m_pauseTime);	

				m_prevTime = startTime;
				m_pauseTime = 0;
				m_bPaused  = false;
			}
		}

		void Timer::Pause()
		{
			if( !m_bPaused )
			{
				m_pauseTime = clock();
				m_bPaused  = true;
			}
		}

	}	// namespace Core
}	//namespace Oak3D