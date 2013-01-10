
#include <iostream>

#include "ro3d.h"
#include "ro3d/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Utils/Timer.h"


namespace ro3d
{
	// --------------------------------------------------------------------------------
	bool ro3dInit( std::vector<std::string> cmdLine )
	{
		std::cout << "Init!" << std::endl;
		ro3d::GetInstance();
		return true;
	}

	// --------------------------------------------------------------------------------
	bool ro3dUpdate()
	{
		ro3d &ro3dRef(ro3d::GetInstance());
		ro3dRef.Update();
		
		static uint32_t count = 0;
		// Run this update routine 5 times
		if(++count == 5)
		{
			return false;
		}

		return true;
	}

	// --------------------------------------------------------------------------------
	void ro3dExit()
	{
		std::cout << "Going out!" << std::endl;
	}


	// --------------------------------------------------------------------------------
	ro3d::ro3d()
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
	void ro3d::Update()
	{
		m_sEngine.Update();
		
		std::cout << "Current time: " << m_sEngine.GetTimer().GetElapsedTime() << std::endl;
	}

	// --------------------------------------------------------------------------------
	ro3d::~ro3d()
	{
		//m_pEngine->Release();
	}
	
	
}	// namespace ro3d
