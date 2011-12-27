
#include "Oak3D.h"
#include "Oak3D/Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngine.h"
#include "Core/Parallel/Thread.h"
#include "Core/Time/Timer.h"


namespace Oak3D
{	

	// --------------------------------------------------------------------------------
	Oak3D::Oak3D()
	{
		m_pEngine = Engine::GetInstance();

		m_pEngine->SetRenderWindow(CreateRenderWindow());		
		m_pEngine->SetTimer(new Core::Timer());
		m_pEngine->SetGraphicsEngine(CreateGraphicsEngine());
		m_pEngine->SetResourceManager(Core::ResourceManager::GetInstance());

		m_pEngine->Initialize();
	}

	// --------------------------------------------------------------------------------
	void Oak3D::Update()
	{
		m_pEngine->Update();
	}

	// --------------------------------------------------------------------------------
	Oak3D::~Oak3D()
	{
		m_pEngine->Release();
	}
	
	
}	// namespace Oak3D
