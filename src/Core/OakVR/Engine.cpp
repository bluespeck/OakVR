#include "Engine.h"
#include "Time/Timer.h"
#include "input/MouseInput/MouseInput.h"
#include "input/KeyboardInput/KeyboardInput.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Log/Log.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/FileLoaders.h"
#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RenderWindow.h"
#include "CameraManager.h"

#include "Renderer/Renderer/Shader.h"
#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"
#include "Renderer/Renderer/Material.h"

#include "Text/Text.h"

#include "Profiler/Profiler.h"


#include <algorithm>
#include <memory>


namespace oakvr
{
		// --------------------------------------------------------------------------------
	bool Engine::Update(double dt)
	{
		oakvr::input::keyboard::Update();
		oakvr::input::mouse::Update();


		if(m_pRW->IsOpen())
		{
			if ((oakvr::input::keyboard::IsDown(oakvr::input::Key::lShift) ||
				oakvr::input::keyboard::IsDown(oakvr::input::Key::rShift))
				&& oakvr::input::keyboard::IsDown(oakvr::input::Key::f5)
				)
				return false;

			// Keep updateables from interfering with the updateables vector while they are updated
			// there is a problem with deleting updateables while the loop is under way in that deleted objects might
			// have Update called for them
			auto pUpdateables = m_pUpdateables;
			for (auto &e : pUpdateables)
				e->Update(dt);

			m_pRenderer->Update(dt);
			profiler::Profiler::GetInstance().PrintSortedData();
		}
		else
		{
			m_pRenderer->Cleanup();
			return false;
		}
		
//		oakvr::Leaf3D::InterfaceFocusManager::GetInstance()->Update();
		//TriggerInputEvents();
//		oakvr::Leaf3D::EventManager::GetInstance()->Update();

		//oakvr::Render::Camera *pCurrentCamera = m_pCM->GetCurrentCamera();
		/*
		if(m_pGE)
		{
			int32_t wd = oakvr::input::MouseInput::GetInstance()->GetWheelDelta();
			if(wd != 0 || ((oakvr::input::MouseInput::GetInstance()->IsLeftButtonDown() || oakvr::input::MouseInput::GetInstance()->IsRightButtonDown()) && oakvr::input::MouseInput::GetInstance()->HasMouseMoved()))
			{
				auto delta = oakvr::input::MouseInput::GetInstance()->GetPositionDelta();


							
				if(oakvr::input::MouseInput::GetInstance()->IsLeftButtonDown())
				{
						pCurrentCamera->Rotate(static_cast<float>(delta.second * dt), static_cast<float>(delta.first * dt), 0.0f);
				}

				if(oakvr::input::MouseInput::GetInstance()->IsRightButtonDown())
				{
					pCurrentCamera->Translate((float)delta.first, (float)delta.second, 0.0f);
				}

				pCurrentCamera->Translate(0.f, 0.f, wd / 20.f);
			}

			oakvr::Math::Matrix *pMatrixView = m_pGE->GetViewMatrix();
			*pMatrixView = m_pGE->CreateViewMatrix(pCurrentCamera->GetPosition(), pCurrentCamera->GetLook(), pCurrentCamera->GetUp());

			m_pGE->ClearBackground(oakvr::Render::Color::Black);

			m_pGE->BeginDraw();
			// update rendered stuff

			DrawAxes();
			//DrawMeshes();
			DrawMeshBoundingBoxes();
			DrawDebugText();
			DrawInterface();
	
			m_pGE->EndDraw();
			m_pGE->SwapBuffers();
			
			
		}
		*/
	}

	// --------------------------------------------------------------------------------
	Engine::Engine()
		: m_pRM{ std::make_shared<oakvr::core::ResourceManager>() }
		, m_pRW{ std::make_shared<oakvr::render::RenderWindow>("oakvr", 2000, 100, 1024, 768) }
		, m_pRenderer{ std::make_shared<oakvr::render::Renderer>() }
		, m_pCM{ std::make_shared<oakvr::render::CameraManager>() }
	{
		m_timer = oakvr::Timer();

		m_pCM = nullptr;
		m_bIsInitialized = false;
	}

	// --------------------------------------------------------------------------------
	Engine::~Engine()
	{		
		//delete m_pGE->GetDebugTextRenderer();
		//oakvr::core::ResourceManager::Release();
//		oakvr::Leaf3D::Widget::ReleaseWidgetList();
//		oakvr::core::IUpdatable::ReleaseUpdatableList();
//		oakvr::Leaf3D::EventManager::Release();
//		oakvr::Leaf3D::InterfaceFocusManager::Release();
		
	}

	// --------------------------------------------------------------------------------
	bool Engine::Initialize()
	{
		oakvr::core::InitializeFileLoaders();

		// Register the files in this path with RM for quick loading into the engine
		m_pRM->AddPathsFromFolder("D:\\Projects\\OakVR\\resources");

		if(!m_pRW || !m_pRW->Initialize())
			return false;

		if(m_pRenderer)
		{
			m_pRenderer->SetRenderWindow(m_pRW);
			m_pRenderer->SetResourceManager(m_pRM);
			m_pRenderer->Initialize();
			
			// Initialize Text manager
			oakvr::core::Text::GetInstance().SetResourceManagerPtr(m_pRM);
			oakvr::core::Text::GetInstance().SetRendererPtr(m_pRenderer);
			oakvr::core::Text::GetInstance().AddFontFace(m_pRM->GetResource("Tinos-Regular"));
		}

		m_timer.Reset();
		m_bIsInitialized = true;
		return true;
//		pm1 = m_pRM->GetResource<oakvr::Render::Mesh>("../resources/Models/hammer.obj");
	}

	void Engine::CleanUp()
	{
		m_pRenderer->Cleanup();
	}

	// --------------------------------------------------------------------------------
	bool Engine::Update()
	{
		m_timer.Tick();
		return Update(m_timer.GetDeltaTime());
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawAxes()
	{
/*		oakvr::Render::Shader *pVertexShader = nullptr;
		oakvr::Render::Shader *pPixelShader = nullptr;

#if (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_9)
		oakvr::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params1.vertexFormat = oakvr::Render::VertexBuffer::eVF_XYZ;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/LinesVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/LinesPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_11)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/LinesVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/LinesPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_OPENGL)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/LinesVS.glsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/LinesPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		//m_pGE->EnableOrtographicProjection();
		m_pGE->EnableFillWireframe();
		//m_pGE->EnableFillSolid();

		oakvr::Render::VertexBuffer vb;
		vb.Create(6, oakvr::Render::VertexBuffer::eVF_XYZ | oakvr::Render::VertexBuffer::eVF_Diffuse);
		float *pBuff = nullptr;
		vb.Lock((void **)&pBuff);
		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;

		*(pBuff++) = 20.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;

		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 20.0f;
		*(pBuff++) = 0.0f;

		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;

		*(pBuff++) = 1.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;

		*(pBuff++) = 0.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 20.0f;

		*(pBuff++) = 1.0f;
		*(pBuff++) = 0.0f;
		*(pBuff++) = 1.0f;
		*(pBuff++) = 1.0f;

		vb.Unlock();

		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(nullptr);
		m_pGE->UseTexture(nullptr);
		m_pGE->UseShader(pVertexShader);
		m_pGE->UseShader(pPixelShader);
		m_pGE->UsePrimitiveTopology(oakvr::Render::ePT_LineList);
		m_pGE->DrawPrimitives(3);
		m_pGE->ReleaseVertexBuffer(&vb);
		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawMeshBoundingBoxes()
	{
		
	}

	// --------------------------------------------------------------------------------
	void Engine::TriggerInputEvents()
	{
		/*
		using Leaf3D::MouseEvent;
		// trigger mouse events
		auto pMouseInput = oakvr::input::MouseInput::GetInstance();
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

		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawInterface()
	{
		/*
		using oakvr::Leaf3D::Widget;
		
		if(Widget::GetWidgetList()->size() == 0)
			return;

		oakvr::Render::Texture *pTexture = GetResourceManager()->GetResource<oakvr::Render::Texture>("../resources/Skins/Button.dds");
		if(!pTexture->IsReady())
			return;

		using oakvr::Render::VertexBuffer;
		oakvr::Render::Shader *pVertexShader = nullptr;
		oakvr::Render::Shader *pPixelShader = nullptr;
#if (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_9)
		oakvr::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params1.vertexFormat = VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/InterfaceVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/InterfacePS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_11)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/InterfaceVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/InterfacePS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_OPENGL)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/InterfaceVS.glsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/InterfacePS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;
		
		m_pGE->EnableOrtographicProjection();
		m_pGE->EnableFillSolid();
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
			using oakvr::Leaf3D::ScreenPosition2D;
			using oakvr::Leaf3D::ScreenSize2D;

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
		oakvr::Render::IndexBuffer ib;
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
		
		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(&ib);
		m_pGE->UseTexture(pTexture);
		m_pGE->UseShader(pVertexShader);
		m_pGE->UseShader(pPixelShader);
		m_pGE->UsePrimitiveTopology(oakvr::Render::ePT_TriangleList);
		m_pGE->DrawIndexedPrimitives(numVertices / 2, numVertices);
		vb.Release();
		ib.Release();
		//m_pRM->ReleaseResource(pVertexShader);

		*/
	}


	void Engine::RegisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		m_pUpdateables.push_back(pUpdateable);
	}

	void Engine::UnregisterUpdateable(std::shared_ptr<oakvr::Updateable> pUpdateable)
	{
		auto it = std::find(m_pUpdateables.begin(), m_pUpdateables.end(), pUpdateable);
		if (it == m_pUpdateables.end())
		{
			Log::PrintError("Trying to unregister an updateable that was not registered! But how can this be?!... ");
		}
		else
		{
			m_pUpdateables.erase(it);
		}
	}

	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------
	// render interface
	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------

	void Engine::RegisterMesh(std::shared_ptr<oakvr::render::Mesh> pMesh)
	{
		m_pRenderer->RegisterMesh(pMesh);
	}

	void Engine::RegisterShader(std::string shaderName)
	{
		m_pRenderer->RegisterShaderProgram(shaderName);
	}

}	// namespace oakvr
