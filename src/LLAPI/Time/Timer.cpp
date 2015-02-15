#include <ctime>
#include <chrono>

#include "Timer.h"

namespace oakvr
{
	static const float s_nanosecond = 1e-9f;

	Timer::Timer(void)
		: m_dt{-1.0}, m_bPaused{false}
	{			
		Reset();
	}

	Timer::~Timer(void)
	{
	}

	auto Timer::Tick() -> void
	{
		if( m_bPaused )
		{
			m_dt = 0.0f;
			return;
		}

		m_currTimePoint = TimePoint::clock::now();
			
		// Time difference between current call and last call of Tick
		m_dt = s_nanosecond * std::chrono::nanoseconds(m_currTimePoint - m_prevTimePoint).count();

		m_prevTimePoint = m_currTimePoint;

		if(m_dt < 0.0f)
		{
			m_dt = 0.0f;
		}
	}

	// Time elapsed since the timer was started (excluding the time it was paused)
	float Timer::GetElapsedTime() const
	{	
		if( m_bPaused )
		{
			return s_nanosecond * std::chrono::nanoseconds(m_pauseTimePoint - m_baseTimePoint).count();
		}
		else
		{
			return s_nanosecond * (std::chrono::nanoseconds(m_currTimePoint - m_baseTimePoint).count() - std::chrono::nanoseconds(m_pausedTimeDuration).count());
		}
	}

	float Timer::GetDeltaTime() const
	{
		return m_dt;
	}

	auto Timer::IsPaused() const -> bool
	{
		return m_bPaused;
	}

	auto Timer::Reset() -> void
	{			
		m_baseTimePoint = TimePoint::clock::now();
		m_prevTimePoint = m_baseTimePoint;
		m_pauseTimePoint = m_baseTimePoint;
		m_bPaused  = false;
	}

	auto Timer::Unpause() -> void
	{			
		if( m_bPaused )
		{
			TimePoint unpauseTimePoint(TimePoint::clock::now());
			m_pausedTimeDuration += unpauseTimePoint - m_pauseTimePoint;	

			m_prevTimePoint = unpauseTimePoint;
			m_bPaused  = false;
		}
	}

	auto Timer::Pause() -> void
	{
		if( !m_bPaused )
		{
			m_pauseTimePoint = TimePoint::clock::now();
			m_bPaused  = true;
		}
	}

}	//namespace oakvr
