

#include "Timer.h"
#include "windows.h"

CTimer::CTimer(void)
: m_secondsPerCount(0.0), m_dt(-1.0), m_baseTime(0), 
m_pausedTime(0), m_prevTime(0), m_currTime(0), m_bPaused(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER *) &countsPerSec);
	m_secondsPerCount = 1.0 / (double)countsPerSec;
}

CTimer::~CTimer(void)
{
}

void CTimer::Tick()
{
	if( m_bPaused )
	{
		m_dt = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER *) &currTime);
	m_currTime = currTime;

	// Time difference between current call and last call of Tick
	m_dt = (m_currTime - m_prevTime) * m_secondsPerCount;

	m_prevTime = m_currTime;

	if(m_dt < 0.0)
	{
		m_dt = 0.0;
	}
}

// Time elapsed since the timer was started (excluding the time it was paused)
float CTimer::GetElapsedTime()const
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

float CTimer::GetDeltaTime()const
{
	return (float)m_dt;
}

bool CTimer::IsPaused()const
{
	return m_bPaused;
}

void CTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER *) &currTime);

	m_baseTime = currTime;
	m_prevTime = currTime;
	m_pauseTime = 0;
	m_bPaused  = false;
}

void CTimer::Unpause()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER *) &startTime);

	if( m_bPaused )
	{
		m_pausedTime += (startTime - m_pauseTime);	

		m_prevTime = startTime;
		m_pauseTime = 0;
		m_bPaused  = false;
	}
}

void CTimer::Pause()
{
	if( !m_bPaused )
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER *) &currTime);

		m_pauseTime = currTime;
		m_bPaused  = true;
	}
}