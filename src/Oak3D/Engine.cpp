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
#include "Renderer/IRenderer/Texture.h"
#include "Renderer/IRenderer/Shader.h"
#ifdef OAK3D_EDITOR
#include "Editor/EditorEntryPoint.h"
#endif

#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9
# include <d3d9.h>
# include "Renderer/DirectX/DirectX9/DirectX9Shader.h"
#elif OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11
# include <d3d11.h>
# include "Renderer/DirectX/DirectX11/DirectX11Shader.h"
#elif OAK3D_RENDERER == OAK3D_RENDERER_OPENGL
# include "Renderer/OpenGL/OpenGLShader.h"
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
#ifdef OAK3D_EDITOR
			Oak3D::Editor::EntryPoint();
#endif
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
			m_pGE->ClearBackground(Oak3D::Render::Color::Black);
			
			m_pGE->BeginDraw();

			char str[128];
			sprintf_s(str, "FPS: %.0f", (1.0f / GetTimer()->GetDeltaTime()));
			m_pGE->OutputText(str, 10, 10);
			
			DrawInterface();
			
			m_pGE->EndDraw();
			m_pGE->SwapBuffers();

			
		}
	}

	// --------------------------------------------------------------------------------
	void Engine::DrawInterface()
	{
		Oak3D::Render::Texture *pTexture = GetResourceManager()->GetResource<Oak3D::Render::Texture>("../resources/Skins/Button.dds");
		if(!pTexture->IsReady())
			return;

		using Oak3D::Render::VertexBuffer;
		Oak3D::Render::Shader *pVertexShader = nullptr;
		Oak3D::Render::Shader *pPixelShader = nullptr;
#if OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_9
		Oak3D::Render::DirectX9Shader::DX9AdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params1.vertexFormat = VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX9Shader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#elif OAK3D_RENDERER == OAK3D_RENDERER_DIRECTX_11
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::DirectX11Shader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#elif OAK3D_RENDERER == OAK3D_RENDERER_OPENGL
		Oak3D::Render::Shader::ShaderAdditionalInitParams params1, params2;
		params1.shaderType = Oak3D::Render::eST_VertexShader;
		params2.shaderType = Oak3D::Render::eST_PixelShader;

		pVertexShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/InterfaceVS.hlsl", &params1);
		pPixelShader	= Oak3D::Engine::GetResourceManager()->GetResource<Oak3D::Render::OpenGLShader>( "../resources/shaders/InterfacePS.hlsl", &params2);
#endif
		if(!pVertexShader->IsReady() || !pPixelShader->IsReady())
			return;
		
		using Oak3D::Leaf3D::Widget;

		if(!Widget::WidgetsAvailable())
			return;

		uint32_t numVertices = 0;
		for(auto it = Widget::s_widgets->begin(); it != Widget::s_widgets->end(); ++it)
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
		Widget::s_widgets->sort([](Widget * w1, Widget * w2)
			{
				return w1->GetDepth() > w2->GetDepth();
			}
		);


		/////
		// Create and populate vertex buffer
		VertexBuffer vb;
		vb.Create(numVertices, VertexBuffer::eVF_XYZ | VertexBuffer::eVF_Tex0);
		
		uint8_t *buff = new uint8_t[vb.GetVertexSize() * vb.GetVertexCount() * Widget::s_widgets->size()];			
		float *p = (float *) buff;

		auto it = Widget::s_widgets->begin();
		while(it != Widget::s_widgets->end())
		{
			using Oak3D::Leaf3D::ScreenPosition;
			using Oak3D::Leaf3D::ScreenSize2D;

			ScreenPosition pos = (*it)->GetPosition();
			ScreenSize2D size = (*it)->GetSize();
			
			*(p++)	= (float)pos.x;
			*(p++)	= (float)pos.y;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= (float)(pos.x + size.width);
			*(p++)	= (float)pos.y;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			*(p++)	= 0.0f;
			
			*(p++)	= (float)pos.x;
			*(p++)	= (float)(pos.y - size.height);
			*(p++)	= 0.0f;
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			
			*(p++)	= (float)(pos.x + size.width);
			*(p++)	= (float)(pos.y - size.height);
			*(p++)	= 0.0f;
			*(p++)	= 1.0f;
			*(p++)	= 1.0f;

			++it;
		}

		void *pBuff = nullptr;
		vb.Lock(&pBuff);
		memcpy(pBuff, buff, vb.GetVertexSize() * vb.GetVertexCount());
		vb.Unlock();
		delete buff;

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
		
		m_pGE->UseShader(pVertexShader);
		m_pGE->UseShader(pPixelShader);
		m_pGE->UseTexture(pTexture);
		m_pGE->UseVertexBuffer(&vb);
		m_pGE->UseIndexBuffer(&ib);
		m_pGE->UsePrimitiveTopology(Oak3D::Render::ePT_TriangleList);
		m_pGE->DrawPrimitives(numVertices / 2);
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
