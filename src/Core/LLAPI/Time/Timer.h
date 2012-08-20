
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_TIMER_H__
#define __OAK3D_INCLUDE_CORE_TIMER_H__

#include <cstdint>

namespace Oak3D
{
	namespace Core
	{

		class Timer
		{
		public:
			Timer();
			virtual ~Timer();

			virtual float GetElapsedTime() const;  // [s]
			virtual float GetDeltaTime() const; // [s]
			virtual bool IsPaused() const; // true if timer is paused

			virtual void Tick();  
			virtual void Unpause(); 
			virtual void Pause();  
			virtual void Reset(); 


		protected:
			double m_secondsPerCount;
			double m_dt;

			int64_t m_baseTime;	
			int64_t m_pauseTime;

			int64_t m_pausedTime;
	
			int64_t m_currTime;
			int64_t m_prevTime;
	
			bool m_bPaused;
		};
	}	// namespace Core
}	// namespace Oak3D

#endif