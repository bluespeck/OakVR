#pragma once

#include <cstdint>
#include <chrono>

namespace oakvr
{
	class Timer
	{
	public:
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
		Timer();
		~Timer();
		double GetElapsedTime() const;  // [s]
		
		virtual double GetDeltaTime() const; // [s]
		virtual bool IsPaused() const; // true if timer is paused
		virtual void Tick();  
		virtual void Unpause(); 
		virtual void Pause();  
		virtual void Reset(); 

		protected:
		double m_dt;

		TimePoint m_baseTimePoint;	
		TimePoint m_pauseTimePoint;

		TimePoint::duration m_pausedTimeDuration;
	
		TimePoint m_currTimePoint;
		TimePoint m_prevTimePoint;
	
		bool m_bPaused;
		};
}	// namespace oakvr
