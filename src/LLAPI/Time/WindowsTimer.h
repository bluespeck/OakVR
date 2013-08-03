
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAKVR_INCLUDE_WINDOWSTIMER_H__
#define __OAKVR_INCLUDE_WINDOWSTIMER_H__

#include "Timer.h"

namespace oakvr
{
	namespace Core
	{

		class WindowsTimer : public Timer
		{
		public:
			WindowsTimer(void);
			~WindowsTimer(void);

			virtual float GetElapsedTime()const;  // [s]
			virtual float GetDeltaTime()const; // [s]
			virtual bool IsPaused()const; // true if timer is paused
			
			virtual void Tick();  
			virtual void Unpause(); 
			virtual void Pause();  
			virtual void Reset(); 
		};
	}	// namespace Core
}	// namespace oakvr

#endif
