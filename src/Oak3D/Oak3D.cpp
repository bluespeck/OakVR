
#include "Oak3D.h"
#include "Oak3DInit.h"

namespace Oak3D
{	

	// --------------------------------------------------------------------------------
	Oak3D::Oak3D()
	{
		// initialize for Windows and DirectX11
		m_pEngine = new Core::Engine();
	
#ifndef OAK3D_WINDOWS
		m_pEngine->SetRenderWindow(CreateRenderWindow());		
#else
		m_pEngine->SetRenderWindow(CreateRenderWindow(reinterpret_cast<HINSTANCE>(m_param)));
#endif

		m_pEngine->SetTimer(CreateTimer());

		m_pEngine->SetGraphicsEngine(CreateGraphicsEngine());		
		m_pEngine->Initialize();
	}

	void Oak3D::Update()
	{
		m_pEngine->Update();
	}

	// --------------------------------------------------------------------------------
	Oak3D::~Oak3D()
	{
		delete m_pEngine;
	}
	
	
}	// namespace Oak3D