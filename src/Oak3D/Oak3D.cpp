
#include "Oak3D.h"
#include "../Core/Engine.h"
#include "../Core/RenderWindow.h"
#include "../Core/ThreadFactory.h"
#include "../Core/Timer.h"
#include "../Core/GraphicsEngine.h"

namespace Oak3D
{	

	// --------------------------------------------------------------------------------
	Oak3D::Oak3D()
	{
		m_pEngine = Core::Engine::GetInstance();

		m_pEngine->SetRenderWindow(CreateRenderWindow());		
		m_pEngine->SetThreadFactory(CreateThreadFactory());
		m_pEngine->SetTimer(CreateTimer());
		m_pEngine->SetGraphicsEngine(CreateGraphicsEngine());		

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
