#include "Engine.h"
#include "Renderer/Renderer/RendererCommon.h"
#include "Time/Timer.h"
#include "ResourceManager/ResourceManager.h"
#include "Input/MouseInput/MouseInput.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"
#include "Log/Log.h"

#	include "Renderer/OpenGL/OpenGLShader.h"


#ifdef OAKVR_EDITOR
#	include "Editor/EditorEntryPoint.h"
#endif

#include <algorithm>
#include <memory>
#include <cassert>

namespace oakvr
{
		// --------------------------------------------------------------------------------
	bool Engine::Update(double dt)
	{
		if(m_pRW->IsOpen())
		{
			m_pRenderer->Update(dt);
			return true;
		}
		else
			return false;
		//oakvr::Input::MouseInput::GetInstance()->Update();
//		oakvr::Leaf3D::InterfaceFocusManager::GetInstance()->Update();
		//TriggerInputEvents();
//		oakvr::Leaf3D::EventManager::GetInstance()->Update();

		//oakvr::Render::Camera *pCurrentCamera = m_pCM->GetCurrentCamera();
		/*
		if(m_pGE)
		{
			int32_t wd = oakvr::Input::MouseInput::GetInstance()->GetWheelDelta();
			if(wd != 0 || ((oakvr::Input::MouseInput::GetInstance()->IsLeftButtonDown() || oakvr::Input::MouseInput::GetInstance()->IsRightButtonDown()) && oakvr::Input::MouseInput::GetInstance()->HasMouseMoved()))
			{
				auto delta = oakvr::Input::MouseInput::GetInstance()->GetPositionDelta();


							
				if(oakvr::Input::MouseInput::GetInstance()->IsLeftButtonDown())
				{
						pCurrentCamera->Rotate(static_cast<float>(delta.second * dt), static_cast<float>(delta.first * dt), 0.0f);
				}

				if(oakvr::Input::MouseInput::GetInstance()->IsRightButtonDown())
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
	{
		m_timer = oakvr::Timer();

		m_pRW = std::make_shared<oakvr::render::RenderWindow>();
		m_pRenderer = std::make_shared<oakvr::render::Renderer>();

		m_pCM = nullptr;
		m_bIsInitialized = false;
	}

	// --------------------------------------------------------------------------------
	Engine::~Engine()
	{
		//delete m_pGE->GetDebugTextRenderer();
		//oakvr::Core::ResourceManager::Release();
		if(m_pRenderer)
		{				
			m_pRenderer->Cleanup();
		}
		
//		oakvr::Leaf3D::Widget::ReleaseWidgetList();
//		oakvr::Core::IUpdatable::ReleaseUpdatableList();
//		oakvr::Leaf3D::EventManager::Release();
//		oakvr::Leaf3D::InterfaceFocusManager::Release();
		
	}

	// --------------------------------------------------------------------------------
	bool Engine::Initialize()
	{
		if(!m_pRW || !m_pRW->Initialize())
			return false;
		if(m_pRenderer)
		{
			m_pRenderer->SetRenderWindow(m_pRW);
			m_pRenderer->Initialize();
			/*
			oakvr::render::DebugTextRenderer *pDebugTextRenderer = nullptr;
#if defined(_WIN32)
			pDebugTextRenderer = new oakvr::render::DirectX9DebugTextRenderer();

			pDebugTextRenderer = new oakvr::render::DirectX11DebugTextRenderer();
#else
			pDebugTextRenderer = new oakvr::render::OpenGLDebugTextRenderer();
#endif
		//	m_pRenderer->SetDebugTextRenderer(pDebugTextRenderer);
			m_pRenderer->Initialize();
			pDebugTextRenderer->Init();
			
			m_pCM.reset(new oakvr::render::CameraManager());
			m_pCM->SetAsCurrentCamera(new oakvr::render::Camera(Vector3(0.f, 0.f, -50.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)));

#ifdef OAKVR_EDITOR
			oakvr::Editor::EntryPoint();
#endif
*/
		}

		m_timer.Reset();
		m_bIsInitialized = true;
		return true;
//		pm1 = m_pRM->GetResource<oakvr::Render::Mesh>("../resources/Models/hammer.obj");
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
		/*
		oakvr::Render::Shader *pVertexShader = nullptr;
		oakvr::Render::Shader *pPixelShader = nullptr;

#if (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_9)
		oakvr::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params1.vertexFormat = oakvr::Render::VertexBuffer::eVF_XYZ;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/BBVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/BBPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_11)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/BBVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/BBPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_OPENGL)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/BBVS.glsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/BBPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		//m_pGE->EnableOrtographicProjection();
		m_pGE->EnableFillWireframe();
		//m_pGE->EnableFillSolid();

		auto pMeshes = oakvr::Render::Mesh::GetMeshList();
		for(auto it = pMeshes->begin(); it != pMeshes->end(); ++it)
		{
			oakvr::Render::Mesh *pMesh = *it;
			if(pMesh->IsReady())
			{
				oakvr::Render::AABB aabb = pMesh->GetBoundingBox();

				oakvr::Render::VertexBuffer vb;
				oakvr::Render::IndexBuffer ib;

				vb.Create(8, oakvr::Render::VertexBuffer::eVF_XYZ);
				ib.Create(36);

				using oakvr::Math::Vector3;
				Vector3 v1 = aabb.m_vecLeftBottomFront;
				Vector3 v2 = aabb.m_vecRightTopBack;
				v1 = Vector3(25.f, 25.f, 1.0f) ;
				v2 = Vector3(50.0f, 50.f, 26.f);
				//v1 = Vector3(-0.5f, -0.5f, 0.4f) ;
				//v2 = Vector3(0.5f, 0.5f, 0.5f);

				Vector3 *pBuff = nullptr;
				vb.Lock((void**)&pBuff);
				Vector3 *pVBData = pBuff;
				*(pVBData++) = v1;
				*(pVBData++) = Vector3(v2.x, v1.y, v1.z);
				*(pVBData++) = Vector3(v2.x, v1.y, v2.z);
				*(pVBData++) = Vector3(v1.x, v1.y, v2.z);
				*(pVBData++) = Vector3(v1.x, v2.y, v1.z);
				*(pVBData++) = Vector3(v2.x, v2.y, v1.z);
				*(pVBData++) = v2;
				*(pVBData++) = Vector3(v1.x, v2.y, v2.z);
				vb.Unlock();

				uint32_t *pIBData = nullptr;
				ib.Lock((void **)&pIBData);
				*(pIBData++) = 0;
				*(pIBData++) = 5;
				*(pIBData++) = 1;

				*(pIBData++) = 0;
				*(pIBData++) = 4;
				*(pIBData++) = 5;

				*(pIBData++) = 7;
				*(pIBData++) = 2;
				*(pIBData++) = 6;

				*(pIBData++) = 7;
				*(pIBData++) = 3;
				*(pIBData++) = 2;
				
				*(pIBData++) = 4;
				*(pIBData++) = 6;
				*(pIBData++) = 5;

				*(pIBData++) = 4;
				*(pIBData++) = 7;
				*(pIBData++) = 6;

				*(pIBData++) = 3;
				*(pIBData++) = 1;
				*(pIBData++) = 2;
				
				*(pIBData++) = 3;
				*(pIBData++) = 0;
				*(pIBData++) = 1;
				
				*(pIBData++) = 1;
				*(pIBData++) = 6;
				*(pIBData++) = 2;

				*(pIBData++) = 1;
				*(pIBData++) = 5;
				*(pIBData++) = 6;

				*(pIBData++) = 3;
				*(pIBData++) = 4;
				*(pIBData++) = 0;

				*(pIBData++) = 3;
				*(pIBData++) = 7;
				*(pIBData++) = 4;

				ib.Unlock();

				m_pGE->UseVertexBuffer(&vb);
				m_pGE->UseIndexBuffer(&ib);
				m_pGE->UseTexture(nullptr);
				m_pGE->UseShader(pVertexShader);
				m_pGE->UseShader(pPixelShader);
				m_pGE->UsePrimitiveTopology(oakvr::Render::ePT_TriangleList);
				m_pGE->DrawIndexedPrimitives(12, 8);
				vb.Release();
				ib.Release();
			}
		}
		//m_pRM->GetInstance()->ReleaseResource(pVertexShader);
		//m_pRM->GetInstance()->ReleaseResource(pPixelShader);

		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawDebugText()
	{
		/*
		m_pGE->EnableFillSolid();

		char str[128];
		sprintf_s(str, "FPS: %.0f", (1.0f / GetTimer()->GetDeltaTime()));
		m_pGE->OutputText(str, 10, 10);

		auto coords = oakvr::Input::MouseInput::GetInstance()->GetPosition();
		sprintf_s(str, "Mouse Coords: %2d,%2d", coords.first, coords.second);
		m_pGE->OutputText(str, 10, 30);
		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawMeshes()
	{
		/*
		oakvr::Render::Shader *pVertexShader = nullptr;
		oakvr::Render::Shader *pPixelShader = nullptr;

#if (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_9)
		oakvr::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params1.vertexFormat = oakvr::Render::VertexBuffer::eVF_XYZ | oakvr::Render::VertexBuffer::eVF_Normal;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/PosNormalVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/PosNormalPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_DIRECTX_11)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/PosNormalVS.hlsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/PosNormalPS.hlsl", &params2);
#elif (OAKVR_RENDERER == OAKVR_RENDERER_OPENGL)
		oakvr::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = oakvr::Render::eST_VertexShader;
		params2.shaderType = oakvr::Render::eST_PixelShader;

		pVertexShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/PosNormalVS.glsl", &params1);
		pPixelShader	= oakvr::Engine::GetResourceManager()->GetResource<oakvr::Render::OpenGLShader>( "../resources/shaders/glsl/PosNormalPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		m_pGE->EnableFillWireframe();

		auto pMeshes = oakvr::Render::Mesh::GetMeshList();
		for(auto it = pMeshes->begin(); it != pMeshes->end(); ++it)
		{
			oakvr::Render::Mesh *pMesh = *it;
			if(pMesh->IsReady())
			{
				oakvr::Render::VertexBuffer vb;
				oakvr::Render::IndexBuffer ib;

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
				m_pGE->UsePrimitiveTopology(oakvr::Render::ePT_TriangleList);
				for(uint32_t i = 0; i < pMesh->m_vMeshElements.size(); ++i)
				{
					// TODO add materials
					//m_pGE->UseTexture(pMesh->m_vMaterials[pMesh->m_vMeshElements[i].m_materialIndex]].)
					m_pGE->DrawIndexedPrimitives(pMesh->m_vMeshElements[i].m_indexCount / 3, pMesh->m_vMeshElements[i].m_startIndex);
					//m_pGE->DrawPrimitives(pMesh->m_vMeshElements[i].m_indexCount / 3);
				}
				vb.Release();
				ib.Release();
			}
		}
		m_pRM->GetInstance()->ReleaseResource(pVertexShader);
		m_pRM->GetInstance()->ReleaseResource(pPixelShader);
		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::TriggerInputEvents()
	{
		/*
		using Leaf3D::MouseEvent;
		// trigger mouse events
		auto pMouseInput = oakvr::Input::MouseInput::GetInstance();
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

	// --------------------------------------------------------------------------------
	bool Engine::IsInitialized()
	{
		return GetInstance().m_bIsInitialized;
	}

	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------
	// render interface
	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------
	ScreenSize Engine::GetScreenSize()
	{
		// TODO: implement GetScreenSize
		ScreenSize temp = {1280, 1024};
		return std::move(temp);
	}

	// --------------------------------------------------------------------------------
	WindowSize Engine::GetWindowSize()
	{
		// TODO: implement using renderwindow
		ScreenSize temp = {1280, 1024};
		return std::move(temp);
	}

}	// namespace oakvr
