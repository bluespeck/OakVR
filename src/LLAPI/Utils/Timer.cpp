#include <ctime>
#include <chrono>

#include "Timer.h"

namespace ro3d
{
	namespace Core
	{
		const double Timer::s_nanosecond = 1.0 / std::chrono::nanoseconds::period::den;

		Timer::Timer(void)
			: m_dt(-1.0), m_bPaused(false)
		{			
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

			m_currTimePoint = TimePoint::clock::now();
			
			// Time difference between current call and last call of Tick
			m_dt = std::chrono::duration_cast<std::chrono::nanoseconds>(m_currTimePoint - m_prevTimePoint).count() * s_nanosecond;

			m_prevTimePoint = m_currTimePoint;

			if(m_dt < 0.0)
			{
				m_dt = 0.0;
			}
		}

		// Time elapsed since the timer was started (excluding the time it was paused)
		double Timer::GetElapsedTime()const
		{	
			if( m_bPaused )
			{
				return std::chrono::duration_cast<std::chrono::nanoseconds>(m_pauseTimePoint - m_baseTimePoint).count() * s_nanosecond;
			}
			else
			{
				return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_currTimePoint - m_baseTimePoint).count() - std::chrono::duration_cast<std::chrono::nanoseconds>(m_pausedTimeDuration).count())* s_nanosecond;
			}
		}

		double Timer::GetDeltaTime()const
		{
			return m_dt;
		}

		bool Timer::IsPaused()const
		{
			return m_bPaused;
		}

		void Timer::Reset()
		{			
			m_baseTimePoint = TimePoint::clock::now();
			m_prevTimePoint = m_baseTimePoint;
			m_pauseTimePoint = m_baseTimePoint;
			m_bPaused  = false;
		}

		void Timer::Unpause()
		{			
			if( m_bPaused )
			{
				TimePoint unpauseTimePoint(TimePoint::clock::now());
				m_pausedTimeDuration += unpauseTimePoint - m_pauseTimePoint;	

				m_prevTimePoint = unpauseTimePoint;
				m_bPaused  = false;
			}
		}

		void Timer::Pause()
		{
			if( !m_bPaused )
			{
				m_pauseTimePoint = TimePoint::clock::now();
				m_bPaused  = true;
			}
		}

	}	// namespace Core
}	//namespace ro3d