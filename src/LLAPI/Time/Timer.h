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
		auto GetElapsedTime() const -> float;  // [s]
		
		virtual auto GetDeltaTime() const -> float; // [s]
		virtual auto IsPaused() const -> bool; // true if timer is paused
		virtual auto Tick() -> void;  
		virtual auto Unpause() -> void; 
		virtual auto Pause() -> void;  
		virtual auto Reset() -> void; 

		private:
		float m_dt;

		TimePoint m_baseTimePoint;	
		TimePoint m_pauseTimePoint;

		TimePoint::duration m_pausedTimeDuration;
	
		TimePoint m_currTimePoint;
		TimePoint m_prevTimePoint;
	
		bool m_bPaused;
	};
}	// namespace oakvr
