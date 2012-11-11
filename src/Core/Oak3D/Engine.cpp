#include <algorithm>
#include <memory>
#include <cassert>

#include "Engine.h"
#include "Renderer/IRenderer/RenderWindow.h"
#include "Renderer/IRenderer/IRenderer.h"
#include "Time/Timer.h"
#include "ResourceManager/ResourceManager.h"
//#include "Leaf3D/Widget.h"
#include "Renderer/IRenderer/VertexBuffer.h"
#include "Renderer/IRenderer/IndexBuffer.h"
#include "Renderer/IRenderer/Color.h"
#include "Renderer/IRenderer/Texture.h"
#include "Renderer/IRenderer/Shader.h"
//#include "Leaf3D/EventManager.h"
//#include "Leaf3D/MouseEvent.h"
//#include "Leaf3D/InterfaceFocusManager.h"
#include "Input/MouseInput/MouseInput.h"
#include "Math/Matrix.h"
#include "Math/Vector3.h"

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
	void Engine::Update(float dt)
	{
		Oak3D::Input::MouseInput::GetInstance()->Update();
//		Oak3D::Leaf3D::InterfaceFocusManager::GetInstance()->Update();
		TriggerInputEvents();
//		Oak3D::Leaf3D::EventManager::GetInstance()->Update();

		Oak3D::Render::Camera *pCurrentCamera = m_pCM->GetCurrentCamera();

		if(m_pGE)
		{
			int32_t wd = Oak3D::Input::MouseInput::GetInstance()->GetWheelDelta();
			if(wd != 0 || ((Oak3D::Input::MouseInput::GetInstance()->IsLeftButtonDown() || Oak3D::Input::MouseInput::GetInstance()->IsRightButtonDown()) && Oak3D::Input::MouseInput::GetInstance()->HasMouseMoved()))
			{
				auto delta = Oak3D::Input::MouseInput::GetInstance()->GetPositionDelta();


							
				if(Oak3D::Input::MouseInput::GetInstance()->IsLeftButtonDown())
				{
						pCurrentCamera->Rotate(delta.second * dt, delta.first * dt, 0.0f);
				}

				if(Oak3D::Input::MouseInput::GetInstance()->IsRightButtonDown())
				{
					pCurrentCamera->Translate((float)delta.first, (float)delta.second, 0.0f);
				}

				pCurrentCamera->Translate(0.f, 0.f, wd / 20.f);
			}

			Oak3D::Math::Matrix *pMatrixView = m_pGE->GetViewMatrix();
			*pMatrixView = m_pGE->CreateViewMatrix(pCurrentCamera->GetPosition(), pCurrentCamera->GetLook(), pCurrentCamera->GetUp());

			m_pGE->ClearBackground(Oak3D::Render::Color::Black);

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
	}

	// --------------------------------------------------------------------------------
	Engine::Engine()
	{
		m_pGE = nullptr;
		m_pRW = nullptr;
		m_pCM = nullptr;
		m_pTimer = nullptr;
		m_pRM = nullptr;
		m_bIsInitialized = false;
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
			m_pGE = nullptr;
		}
		if(m_pRW)
		{
			delete m_pRW;
			m_pRW = nullptr;
		}
		if(m_pCM)
		{
			delete m_pCM;
			m_pCM = nullptr;
		}
		if(m_pTimer)
		{
			delete m_pTimer;
			m_pTimer = nullptr;
		}
//		Oak3D::Leaf3D::Widget::ReleaseWidgetList();
//		Oak3D::Core::IUpdatable::ReleaseUpdatableList();
//		Oak3D::Leaf3D::EventManager::Release();
//		Oak3D::Leaf3D::InterfaceFocusManager::Release();
		
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
			m_pCM = new Oak3D::Render::CameraManager();
			m_pCM->SetAsCurrentCamera(new Oak3D::Render::Camera(Vector3(0.f, 0.f, -50.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)));

#ifdef OAK3D_EDITOR
			Oak3D::Editor::EntryPoint();
#endif
		}

		if(m_pTimer)
		{
			m_pTimer->Reset();
		}
		m_bIsInitialized = true;

//		pm1 = m_pRM->GetResource<Oak3D::Render::Mesh>("../resources/Models/hammer.obj");
	}

	// --------------------------------------------------------------------------------
	void Engine::Update()
	{
		m_pTimer->Tick();
		Update(m_pTimer->GetDeltaTime());
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawAxes()
	{
/*		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;

#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = Oak3D::Render::VertexBuffer::eVF_XYZ;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/LinesVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/LinesPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/LinesVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/LinesPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/LinesVS.glsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/LinesPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		//m_pGE->EnableOrtographicProjection();
		m_pGE->EnableFillWireframe();
		//m_pGE->EnableFillSolid();

		Oak3D::Render::VertexBuffer vb;
		vb.Create(6, Oak3D::Render::VertexBuffer::eVF_XYZ | Oak3D::Render::VertexBuffer::eVF_Diffuse);
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
		m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_LineList);
		m_pGE->DrawPrimitives(3);
		m_pGE->ReleaseVertexBuffer(&vb);
		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawMeshBoundingBoxes()
	{
		/*
		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;

#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = Oak3D::Render::VertexBuffer::eVF_XYZ;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/BBVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/BBPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/BBVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/BBPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/BBVS.glsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/BBPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		//m_pGE->EnableOrtographicProjection();
		m_pGE->EnableFillWireframe();
		//m_pGE->EnableFillSolid();

		auto pMeshes = Oak3D::Render::Mesh::GetMeshList();
		for(auto it = pMeshes->begin(); it != pMeshes->end(); ++it)
		{
			Oak3D::Render::Mesh *pMesh = *it;
			if(pMesh->IsReady())
			{
				Oak3D::Render::AABB aabb = pMesh->GetBoundingBox();

				Oak3D::Render::VertexBuffer vb;
				Oak3D::Render::IndexBuffer ib;

				vb.Create(8, Oak3D::Render::VertexBuffer::eVF_XYZ);
				ib.Create(36);

				using Oak3D::Math::Vector3;
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
				m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
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

		auto coords = Oak3D::Input::MouseInput::GetInstance()->GetPosition();
		sprintf_s(str, "Mouse Coords: %2d,%2d", coords.first, coords.second);
		m_pGE->OutputText(str, 10, 30);
		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawMeshes()
	{
		/*
		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;

#if (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9)
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = Oak3D::Render::VertexBuffer::eVF_XYZ | Oak3D::Render::VertexBuffer::eVF_Normal;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/PosNormalVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/PosNormalPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/PosNormalVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/PosNormalPS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/PosNormalVS.glsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/PosNormalPS.glsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;

		m_pGE->EnablePerspectiveProjection();
		m_pGE->EnableFillWireframe();

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

		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawInterface()
	{
		/*
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

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/hlsl_2_0/InterfacePS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/hlsl_4_0/InterfacePS.hlsl", &params2);
#elif (OAK3D_RENDERER == OAK3D_RENDERER_OPENGL)
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/InterfaceVS.glsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/glsl/InterfacePS.glsl", &params2);
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
		
		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(&ib);
		m_pGE->UseTexture(pTexture);
		m_pGE->UseShader(pVertexShader);
		m_pGE->UseShader(pPixelShader);
		m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
		m_pGE->DrawIndexedPrimitives(numVertices / 2, numVertices);
		vb.Release();
		ib.Release();
		//m_pRM->ReleaseResource(pVertexShader);

		*/
	}

	// --------------------------------------------------------------------------------
	void Engine::SetRenderer(Render::IRenderer *pGE)
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
	Render::IRenderer *Engine::GetRenderer()
	{
		return m_pInstance->m_pGE;
	}

	// --------------------------------------------------------------------------------
	bool Engine::IsInitialized()
	{
		return m_pInstance->m_bIsInitialized;
	}
}	// namespace Oak3D
