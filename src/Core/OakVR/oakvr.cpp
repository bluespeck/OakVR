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
		return OakVR::GetInstance().Update();
	}

	// --------------------------------------------------------------------------------
	void oakvrExit()
	{
		Log::PrintInfo("OakVR shutting down!\n");
	}


	// --------------------------------------------------------------------------------
	OakVR::OakVR()
	:	m_sEngine (Engine::GetInstance())
	{
		if(!m_sEngine.Initialize())
		{
			Log::PrintError("Failed to initialize OakVR!\n");
			exit(1);
		}
	}

	

	// --------------------------------------------------------------------------------
	bool OakVR::Update()
	{
		return m_sEngine.Update();
		
		//std::cout << "Current time: " << m_sEngine.GetTimer().GetElapsedTime() << std::endl;
	}

	// --------------------------------------------------------------------------------
	OakVR::~OakVR()
	{
	}
	
	
}	// namespace oakvr
