
#include <iostream>

#include "oakvr.h"
#include "OakVR/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Time/Timer.h"
#include "Log/Log.h"


namespace oakvr
{
	// --------------------------------------------------------------------------------
	bool oakvrInit( std::vector<std::string> cmdLine )
	{
		Log::SetMaxLevel(Log::LogLevel::info);
		Log::Print(Log::LogLevel::info, " OakVR Init\n");
		oakvr::GetInstance();
		return true;
	}

	// --------------------------------------------------------------------------------
	bool oakvrUpdate()
	{
		oakvr &oakvrRef = oakvr::GetInstance();
		oakvrRef.Update();
		
		static uint32_t count = 0;
		// Run this update routine 5 times
		if(++count == 5)
		{
			return false;
		}

		return true;
	}

	// --------------------------------------------------------------------------------
	void oakvrExit()
	{
		Log::Print(Log::LogLevel::info, " OakVR closing!\n");

	}


	// --------------------------------------------------------------------------------
	oakvr::oakvr()
	:	m_sEngine (Engine::GetInstance())
	{
		

	/*	m_pEngine->SetRenderWindow(CreateRenderWindow());		
		m_pEngine->SetTimer(new Core::Timer());
		m_pEngine->SetRenderer(CreateRenderer());
		m_pEngine->SetResourceManager(Core::ResourceManager::GetInstance());
*/
		m_sEngine.Initialize();
	}

	

	// --------------------------------------------------------------------------------
	void oakvr::Update()
	{
		m_sEngine.Update();
		
		std::cout << "Current time: " << m_sEngine.GetTimer().GetElapsedTime() << std::endl;
	}

	// --------------------------------------------------------------------------------
	oakvr::~oakvr()
	{
		//m_pEngine->Release();
	}
	
	
}	// namespace oakvr
