
#include <iostream>

#include "ro3d.h"
#include "ro3d/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Utils/Timer.h"


namespace ro3d
{	
	bool ro3dInit( std::vector<std::string> cmdLine )
	{
		std::cout << "Init!" << std::endl;
		return true;
	}

	bool ro3dUpdate()
	{
		static uint8_t count = 0;
		std::cout << "This is stuff" << std::endl;
		if(count++ == 5)
			return false;
		return true;
	}

	void ro3dExit()
	{
		std::cout << "Going out!" << std::endl;
	}


	// --------------------------------------------------------------------------------
	ro3d::ro3d()
	{
		m_pEngine = Engine::GetInstance();

	/*	m_pEngine->SetRenderWindow(CreateRenderWindow());		
		m_pEngine->SetTimer(new Core::Timer());
		m_pEngine->SetRenderer(CreateRenderer());
		m_pEngine->SetResourceManager(Core::ResourceManager::GetInstance());
*/
		m_pEngine->Initialize();
	}

	// --------------------------------------------------------------------------------
	void ro3d::Update()
	{
		m_pEngine->Update();
	}

	// --------------------------------------------------------------------------------
	ro3d::~ro3d()
	{
		m_pEngine->Release();
	}
	
	
}	// namespace ro3d
