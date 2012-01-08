#include <algorithm>
#include <memory>
#include <cassert>

#include "Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngine.h"
#include "Core/Time/Timer.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Leaf3D/Widget.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Color.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Engine::Engine()
	{
		m_pGE = nullptr;
		m_pRW = nullptr;
		m_pTimer = nullptr;
		m_pRM = nullptr;
		m_bIsInitialized = false;
	}

	// --------------------------------------------------------------------------------
	Engine::~Engine()
	{
		if(m_pGE)
		{				
			delete m_pGE;
		}
		if(m_pRW)
			delete m_pRW;
		if(m_pTimer)
			delete m_pTimer;
	}

	// --------------------------------------------------------------------------------
	void Engine::Initialize()
	{
		if(m_pGE && m_pRW)
		{
			m_pRW->Initialize();
			m_pGE->SetRenderWindow(m_pRW);
			m_pGE->Initialize();
			m_pRM->Initialize();
		}

		if(m_pTimer)
		{
			m_pTimer->Reset();
		}
		m_bIsInitialized = true;
	}

	// --------------------------------------------------------------------------------
	void Engine::Update()
	{
		m_pTimer->Tick();
		Update(m_pTimer->GetDeltaTime());
	}

	// --------------------------------------------------------------------------------
	void Engine::Update(float dt)
	{
		if(m_pGE)
		{
			// update engine stuff

			// render scene
			m_pGE->Render();

			DrawInterface();
		}
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawInterface()
	{		
		using Oak3D::Leaf3D::Widget;

		if(Widget::s_widgets.size() == 0)
			return;

		uint32_t numVertices = 0;
		for(auto it = Widget::s_widgets.begin(); it != Widget::s_widgets.end(); ++it)
		{
			if((*it)->IsVisible())
			{
				numVertices += 4;
			}
		}

		assert(numVertices != 0 && "There is nothing for DrawInterface to draw!!!");
		if(numVertices == 0)
			return;

		/////
		// Sort widget list in reverse depth order
		Widget::s_widgets.sort([](Widget * w1, Widget * w2)
			{
				return w1->GetDepth() > w2->GetDepth();
			}
		);


		/////
		// Create and populate vertex buffer
		using Oak3D::Render::VertexBuffer;		
		VertexBuffer vb;
		vb.Create(numVertices, VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0);
		
		uint8_t *buff = new uint8_t[vb.GetVertexSize() * vb.GetVertexCount()];			
		float *p = (float *) buff;

		auto it = Widget::s_widgets.begin();
		while(it != Widget::s_widgets.end())
		{
			using Oak3D::Leaf3D::ScreenPosition;
			using Oak3D::Leaf3D::ScreenSize2D;

			ScreenPosition pos = (*it)->GetPosition();
			ScreenSize2D size = (*it)->GetSize();
			
			*(p++)	= pos.x;
			*(p++)	= pos.y;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= pos.x + size.width;
			*(p++)	= pos.y;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= pos.x;
			*(p++)	= pos.y - size.height;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			
			*(++p)	= pos.x + size.width;
			*(++p)	= pos.y - size.height;
			*(++p)	= 0.0f;
			*(++p)	= 1.0f;
			*(++p)	= 1.0f;

			++it;
		}

		void *pBuff = nullptr;
		vb.Lock(&pBuff);
		memcpy(pBuff, buff, vb.GetVertexSize() * vb.GetVertexCount());
		vb.Unlock();
		delete[] buff;

		/////
		// Create associated index buffer
		Oak3D::Render::IndexBuffer ib;
		ib.Create(numVertices);

		buff = new uint8_t[6 * numVertices];	// 6 indices for every 4 vertices, each having 4 bytes
		uint32_t *pp = (uint32_t *)buff;
		for(uint32_t i = 0; i < numVertices; i += 4)
		{
			*(pp++) = i + 0;
			*(pp++) = i + 1;
			*(pp++) = i + 2;
			*(pp++) = i + 2;
			*(pp++) = i + 1;
			*(pp++) = i + 3;
		}

		pBuff = nullptr;
		ib.Lock(&pBuff);
		memcpy(pBuff, buff, 6 * numVertices);
		ib.Unlock();
		delete[] buff;
		buff = nullptr;

		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(&ib);
		m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
		m_pGE->ClearBackground(Oak3D::Render::Color::Black);
		// TODO Draw with this vb

	}

	// --------------------------------------------------------------------------------
	void Engine::SetGraphicsEngine(Render::GraphicsEngine *pGE)
	{
		if(m_pInstance->m_pGE)
			delete m_pInstance->m_pGE;
		m_pInstance->m_pGE = pGE;
	}

	// --------------------------------------------------------------------------------
	void Engine::SetResourceManager(Core::ResourceManager *pRM)
	{
		m_pInstance->m_pRM = Core::ResourceManager::GetInstance();
	}

	// --------------------------------------------------------------------------------
	Core::ResourceManager *Engine::GetResourceManager()
	{
		return m_pInstance->m_pRM;
	}

	// --------------------------------------------------------------------------------
	void Engine::SetRenderWindow(Render::RenderWindow *pRW)
	{
		if(m_pInstance->m_pRW)
			delete m_pInstance->m_pRW;
		m_pInstance->m_pRW = pRW;
	}

	// --------------------------------------------------------------------------------
	Render::RenderWindow *Engine::GetRenderWindow()
	{
		return m_pInstance->m_pRW;
	}

	// --------------------------------------------------------------------------------
	void Engine::SetTimer(Core::Timer *pTimer)
	{
		if(m_pInstance->m_pTimer)
			delete m_pInstance->m_pTimer;
		m_pInstance->m_pTimer = pTimer;
	}

	Core::Timer *Engine::GetTimer()
	{
		// --------------------------------------------------------------------------------
		return m_pInstance->m_pTimer;
	}

	// --------------------------------------------------------------------------------
	Render::GraphicsEngine *Engine::GetGraphicsEngine()
	{
		return m_pInstance->m_pGE;
	}

	// --------------------------------------------------------------------------------
	bool Engine::IsInitialized()
	{
		return m_pInstance->m_bIsInitialized;
	}
}	// namespace Oak3D
