#include "oakvr.h"
#include "OakVR/Engine.h"
#include "Time/Timer.h"
#include "Log/Log.h"

#include <iostream>

namespace oakvr
{
	// --------------------------------------------------------------------------------
	bool oakvrInit( std::vector<std::string> cmdLine )
	{
		Log::SetMaxLevel(Log::LogLevel::info);
		return true;
	}

	// --------------------------------------------------------------------------------
	bool oakvrUpdate()
	{
		oakvr::GetInstance().Update();

//		static uint32_t count = 0;
//		// Run this update routine 5 times
//		if(++count == 5)
//		{
//			return false;
//		}

		return true;
	}

	// --------------------------------------------------------------------------------
	void oakvrExit()
	{
		Log::PrintInfo(" OakVR shutting down!\n");

	}


	// --------------------------------------------------------------------------------
	oakvr::oakvr()
	:	m_sEngine (Engine::GetInstance())
	{
		m_sEngine.Initialize();
	}

	

	// --------------------------------------------------------------------------------
	void oakvr::Update()
	{
		m_sEngine.Update();
		
		//std::cout << "Current time: " << m_sEngine.GetTimer().GetElapsedTime() << std::endl;
	}

	// --------------------------------------------------------------------------------
	oakvr::~oakvr()
	{
		//m_pEngine->Release();
	}
	
	
}	// namespace oakvr
