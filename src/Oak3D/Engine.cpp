#include <algorithm>
#include <memory>
#include <cassert>

#include "Core/Config/Oak3DConfig.h"

#include "Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/GraphicsEngine.h"
#include "Core/Time/Timer.h"
#include "Core/ResourceManager/ResourceManager.h"
#include "Leaf3D/Widget.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Color.h"
#include "Renderer/IRenderer/Texture.h"
#include "Renderer/IRenderer/Shader.h"
#include "Leaf3D/EventManager.h"
#include "Leaf3D/MouseEvent.h"
#include "Leaf3D/InterfaceFocusManager.h"
#include "Input/MouseInput.h"

#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
# include "Renderer/DirectX/DirectX9/DirectX9Shader.h"
# include "Renderer/DirectX/DirectX9/DirectX9DebugTextRenderer.h"
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
# include "Renderer/DirectX/DirectX11/DirectX11DebugTextRenderer.h"
# include "Renderer/DirectX/DirectX11/DirectX11Shader.h"
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
# include "Renderer/OpenGL/OpenGLShader.h"
# include "Renderer/OpenGL/OpenGLDebugTextRenderer.h"
#endif

#ifdef OAK3D_EDITOR
#include "Editor/EditorEntryPoint.h"
#endif


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
		b1.SetPosition(100, 100);
		b1.SetDepth(0);
		b1.SetSize(64, 32);

		b2.SetPosition(250, 100);
		b2.SetDepth(1);
		b2.SetSize(200, 100);

		b3.SetPosition(240, 110);
		b3.SetDepth(0);
		b3.SetSize(70, 20);

		b4.SetPosition(230, 120);
		b4.SetDepth(2);
		b4.SetSize(70, 20);

		b5.SetPosition(220, 130);
		b5.SetDepth(3);
		b5.SetSize(70, 20);

		pm1 = nullptr;
	}

	// --------------------------------------------------------------------------------
	Engine::~Engine()
	{
		delete m_pGE->GetDebugTextRenderer();
		Oak3D::Core::ResourceManager::Release();
		if(m_pGE)
		{				
			m_pGE->Cleanup();
			delete m_pGE;
		}
		if(m_pRW)
			delete m_pRW;
		if(m_pTimer)
			delete m_pTimer;
		Oak3D::Leaf3D::Widget::ReleaseWidgetList();
		Oak3D::Core::IUpdatable::ReleaseUpdatableList();
		Oak3D::Leaf3D::EventManager::Release();
		Oak3D::Leaf3D::InterfaceFocusManager::Release();
		
	}

	// --------------------------------------------------------------------------------
	void Engine::Initialize()
	{
		if(m_pGE && m_pRW)
		{
			m_pRW->Initialize();
			m_pGE->SetRenderWindow(m_pRW);
			Oak3D::Render::DebugTextRenderer *pDebugTextRenderer = nullptr;			
# if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
			pDebugTextRenderer = new Oak3D::Render::DirectX9DebugTextRenderer();
# elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
			pDebugTextRenderer = new Oak3D::Render::DirectX11DebugTextRenderer();
# elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
			pDebugTextRenderer = new Oak3D::Render::OpenGLDebugTextRenderer();
# endif
			m_pGE->SetDebugTextRenderer(pDebugTextRenderer);
			m_pGE->Initialize();
			pDebugTextRenderer->Init();
			m_pRM->Initialize();
#ifdef OAK3D_EDITOR
			Oak3D::Editor::EntryPoint();
#endif
		}

		if(m_pTimer)
		{
			m_pTimer->Reset();
		}
		m_bIsInitialized = true;

		pm1 = m_pRM->GetResource<Oak3D::Render::Mesh>("../resources/Models/hammer.obj");
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
		Oak3D::Input::MouseInput::GetInstance()->Update();
		Oak3D::Leaf3D::InterfaceFocusManager::GetInstance()->Update();
		TriggerInputEvents();
		Oak3D::Leaf3D::EventManager::GetInstance()->Update();

		if(m_pGE)
		{
			m_pGE->ClearBackground(Oak3D::Render::Color::Black);

			m_pGE->BeginDraw();

			// update engine stuff
			DrawMeshes();

			/////
			// Draw debug text
			char str[128];
			sprintf_s(str, "FPS: %.0f", (1.0f / GetTimer()->GetDeltaTime()));
			m_pGE->OutputText(str, 10, 10);

			auto coords = Oak3D::Input::MouseInput::GetInstance()->GetPosition();
			sprintf_s(str, "Mouse Coords: %2d,%2d", coords.first, coords.second);
			m_pGE->OutputText(str, 10, 30);
			
			
			DrawInterface();
			
			m_pGE->EndDraw();
			m_pGE->SwapBuffers();

			
		}
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawMeshes()
	{
		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;

#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = Oak3D::Render::VertexBuffer::eVF_XYZ | Oak3D::Render::VertexBuffer::eVF_Normal;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/PosNormalVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/PosNormalPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/PosNormalVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/PosNormalPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/PosNormalVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/PosNormalPS.hlsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		auto pMeshes = Oak3D::Render::Mesh::GetMeshList();
		for(auto it = pMeshes->begin(); it != pMeshes->end(); ++it)
		{
			Oak3D::Render::Mesh *pMesh = *it;
			if(pMesh->IsReady())
			{
				Oak3D::Render::VertexBuffer vb;
				Oak3D::Render::IndexBuffer ib;

				vb.Create(pMesh->m_vertexCount, pMesh->m_vertexFormat);
				ib.Create(pMesh->m_indexCount);

				void *pVB = nullptr;
				void *pIB = nullptr;
				vb.Lock(&pVB);
				memcpy(pVB, pMesh->m_pVertexData, pMesh->m_vertexCount * pMesh->m_vertexSize);
				vb.Unlock();
				ib.Lock(&pIB);
				memcpy(pIB, pMesh->m_pIndexData, pMesh->m_indexCount * sizeof(uint32_t));
				ib.Unlock();

				m_pGE->UseVertexBuffer(&vb);
				m_pGE->UseIndexBuffer(&ib);
				m_pGE->UseTexture(nullptr);
				m_pGE->UseShader(pVertexShader);
				m_pGE->UseShader(pPixelShader);
				m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
				for(uint32_t i = 0; i < pMesh->m_vMeshElements.size(); ++i)
				{
					// TODO add materials
					//m_pGE->UseTexture(pMesh->m_vMaterials[pMesh->m_vMeshElements[i].m_materialIndex]].)
					m_pGE->DrawIndexedPrimitives(pMesh->m_vMeshElements[i].m_indexCount / 3, pMesh->m_vMeshElements[i].m_startIndex);
				}
				vb.Release();
				ib.Release();
			}
		}
		m_pRM->GetInstance()->ReleaseResource(pVertexShader);
		m_pRM->GetInstance()->ReleaseResource(pPixelShader);
	}

	// --------------------------------------------------------------------------------
	void Engine::TriggerInputEvents()
	{
		using Leaf3D::MouseEvent;
		// trigger mouse events
		auto pMouseInput = Oak3D::Input::MouseInput::GetInstance();
		MouseEvent ev;
		ev.m_mouseData.m_bLButtonDown = pMouseInput->IsLeftButtonDown();
		ev.m_mouseData.m_bLButtonDown = pMouseInput->IsMiddleButtonDown();
		ev.m_mouseData.m_bRButtonDown = pMouseInput->IsRightButtonDown();
		ev.m_mouseData.m_mousePosition.x = pMouseInput->GetPosition().first;
		ev.m_mouseData.m_mousePosition.y = pMouseInput->GetPosition().second;
		ev.m_mouseData.m_wheelDelta = pMouseInput->GetWheelDelta();
		if(pMouseInput->IsLeftButtonDown())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeLButtonDown);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsLeftButtonHeld())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeLButtonHeld);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
			else
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeLButtonPressed);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}
		else if(pMouseInput->IsLeftButtonUp())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeLButtonUp);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsLeftButtonReleased())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeLButtonReleased);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}

		if(pMouseInput->IsMiddleButtonDown())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeMButtonDown);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsMiddleButtonHeld())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeMButtonHeld);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
			else
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeMButtonPressed);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}
		else if(pMouseInput->IsMiddleButtonUp())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeMButtonUp);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsMiddleButtonReleased())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeMButtonReleased);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}

		if(pMouseInput->IsRightButtonDown())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeRButtonDown);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsRightButtonHeld())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeRButtonHeld);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
			else
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeRButtonPressed);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}
		else if(pMouseInput->IsRightButtonUp())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeRButtonUp);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);

			if(pMouseInput->IsRightButtonReleased())
			{
				MouseEvent *pev = new MouseEvent();
				pev->m_mouseData = ev.m_mouseData;
				pev->SetEventSubType(ev.eventSubtypeRButtonReleased);
				Leaf3D::EventManager::GetInstance()->AddEvent(pev);
			}
		}

		if(pMouseInput->HasMouseMoved())
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeMouseMoved);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);
		}

		if(pMouseInput->GetWheelDelta() != 0)
		{
			MouseEvent *pev = new MouseEvent();
			pev->m_mouseData = ev.m_mouseData;
			pev->SetEventSubType(ev.eventSubtypeMouseWheel);
			Leaf3D::EventManager::GetInstance()->AddEvent(pev);
		}
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawInterface()
	{
		using Oak3D::Leaf3D::Widget;

		if(Widget::GetWidgetList()->size() == 0)
			return;

		Oak3D::Render::Texture *pTexture = GetResourceManager()->GetResource<Oak3D::Render::Texture>("../resources/Skins/Button.dds");
		if(!pTexture->IsReady())
			return;

		using Oak3D::Render::VertexBuffer;
		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;
#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;
		
		auto widgets = Widget::GetWidgetList();

		uint32_t numVertices = 0;
		for(auto it = widgets->begin(); it != widgets->end(); ++it)
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
		widgets->sort([](Widget * w1, Widget * w2)
			{
				return w1->GetDepth() > w2->GetDepth();
			}
		);


		/////
		// Create and populate vertex buffer
		VertexBuffer vb;
		vb.Create(numVertices, VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0);
		
		uint8_t *buff = new uint8_t[vb.GetVertexSize() * vb.GetVertexCount() * widgets->size()];			
		float *p = (float *) buff;

		float hw = GetRenderWindow()->GetWidth() / 2.f;
		float hh = GetRenderWindow()->GetHeight() / 2.f;

		float invWidth = 1.0f / hw;
		float invHeight = 1.0f / hh;

		auto it = widgets->begin();
		while(it != widgets->end())
		{
			using Oak3D::Leaf3D::ScreenPosition2D;
			using Oak3D::Leaf3D::ScreenSize2D;

			ScreenPosition2D pos = (*it)->GetPosition();
			ScreenSize2D size = (*it)->GetSize();
			float fx = (pos.x - hw) * invWidth;
			float fy = (hh - pos.y) * invHeight;
			float fw = size.width * invWidth;
			float fh = size.height * invHeight;

			*(p++)	= fx;
			*(p++)	= fy;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= fx + fw;
			*(p++)	= fy;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= fx + fw;
			*(p++)	= fy - fh;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			*(p++)	= 1.0f;
			
			*(p++)	= fx;
			*(p++)	= fy - fh;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;

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
		ib.Create(numVertices * 6 / 4);

		buff = new uint8_t[6 * numVertices];	// 6 indices for every 4 vertices, each having 4 bytes
		uint32_t *pp = (uint32_t *)buff;
		for(uint32_t i = 0; i < numVertices; i += 4)
		{
			*(pp++) = i + 0;
			*(pp++) = i + 1;
			*(pp++) = i + 3;
			*(pp++) = i + 1;
			*(pp++) = i + 2;
			*(pp++) = i + 3;
		}

		pBuff = nullptr;
		ib.Lock(&pBuff);
		memcpy(pBuff, buff, 6 * numVertices);
		ib.Unlock();
		delete[] buff;
		buff = nullptr;
		
		m_pGE->UseShader(pVertexShader);
		m_pGE->UseShader(pPixelShader);
		m_pGE->UseTexture(pTexture);
		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(&ib);
		m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
		m_pGE->DrawIndexedPrimitives(numVertices / 2);
		vb.Release();
		ib.Release();
		m_pRM->ReleaseResource(pVertexShader);
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
