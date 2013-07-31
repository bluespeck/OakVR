
#include <iostream>

#include "oakvr.h"
#include "OakVR/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Utils/Timer.h"


namespace oakvr
{
	// --------------------------------------------------------------------------------
	bool oakvrInit( std::vector<std::string> cmdLine )
	{
		std::cout << "Init!" << std::endl;
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
		std::cout << "Going out!" << std::endl;
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
