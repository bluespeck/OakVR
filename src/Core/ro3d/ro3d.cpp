
#include "ro3d.h"
#include "ro3d/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Parallel/Thread.h"
#include "Time/Timer.h"

namespace ro3d
{	

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
