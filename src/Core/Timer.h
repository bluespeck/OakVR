#pragma once

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	float GetElapsedTime()const;  // [s]
	float GetDeltaTime()const; // [s]
	bool IsPaused()const; // true if timer is paused

	void Tick();  
	void Unpause(); 
	void Pause();  
	void Reset(); 


private:
	double m_secondsPerCount;
	double m_dt;

	__int64 m_baseTime;	
	__int64 m_pauseTime;

	__int64 m_pausedTime;
	
	__int64 m_currTime;
	__int64 m_prevTime;
	
	bool m_bPaused;
};