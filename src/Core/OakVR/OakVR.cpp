#include "OakVR.h"
#include "Time/Timer.h"
#include "input/MouseInput/MouseInput.h"
#include "input/KeyboardInput/KeyboardInput.h"


#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RenderWindow.h"

#include "Text/Text.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/FileLoaders.h"
#include "Console/Console.h"

#include "Profiler/Profiler.h"
#include "Log/Log.h"

#include <algorithm>
#include <memory>


namespace oakvr
{
	// --------------------------------------------------------------------------------
	bool OakVR::Update(TimeDeltaType dt)
	{
		PROFILER_FUNC_SCOPED_TIMER;
		oakvr::input::keyboard::Update();
		oakvr::input::mouse::Update();


		if (m_pRW->IsOpen())
		{
			if ((oakvr::input::keyboard::IsDown(oakvr::input::Key::lShift) ||
				oakvr::input::keyboard::IsDown(oakvr::input::Key::rShift))
				&& oakvr::input::keyboard::IsDown(oakvr::input::Key::f5)
				)
				return false;

			// Keep Updatables from interfering with the Updatables vector while they are updated
			// there is a problem with deleting Updatables while the loop is under way in that deleted objects might
			// have Update called for them
			auto pUpdatables = m_pUpdatables;
			for (auto &e : pUpdatables)
				if (!e->Update(dt))
					return false;
			auto pCamera = GetCurrentCamera();
			static oakvr::Frustum frustum = pCamera->GetFrustum();
			if (pCamera)
			{
				m_pRenderer->SetCurrentCamera(pCamera);
				m_pRenderer->SetViewMatrix(pCamera->ComputeViewMatrix());
				m_pRenderer->SetProjMatrix(pCamera->GetProjMatrix());
			}
			m_pRenderer->Update(dt);
		}
		else
		{
			m_pRenderer->Cleanup();
			return false;
		}

		oakvr::profiler::Profiler::GetInstance().PrintSortedData();
		return true;
	}

	// --------------------------------------------------------------------------------
	OakVR::OakVR()
		: m_pRM{ std::make_shared<oakvr::core::ResourceManager>() }
		
	{
		m_timer = oakvr::Timer();

		Initialize();
	}

	// --------------------------------------------------------------------------------
	OakVR::~OakVR()
	{
		Cleanup();
	}

	// --------------------------------------------------------------------------------
	// callback functions begin
	// --------------------------------------------------------------------------------

	void WindowSizeChangedCallback(void *pNativeHandler, int width, int height)
	{
		oakvr::OakVR::GetInstance().OnWindowSizeChanged(pNativeHandler, width, height);
	}

	void WindowFocusChangedCallback(void *pNativeHandler, int focused)
	{
		oakvr::OakVR::GetInstance().OnWindowFocusChanged(pNativeHandler, focused);
	}

	void WindowPositionChangedCallback(void *pNativeHandler, int x, int y)
	{
		oakvr::OakVR::GetInstance().OnWindowPositionChanged(pNativeHandler, x, y);
	}

	// --------------------------------------------------------------------------------
	// callback functions end
	// --------------------------------------------------------------------------------


	// --------------------------------------------------------------------------------
	bool OakVR::Initialize()
	{
		oakvr::core::InitializeFileLoaders();

		if (!m_pRW || !m_pRW->Initialize())
			return false;

		// Configure callbacks for necessary render window events
		m_pRW->SetWindowSizeCallback(WindowSizeChangedCallback);
		m_pRW->SetWindowFocusCallback(WindowFocusChangedCallback);
		m_pRW->SetWindowPositionCallback(WindowPositionChangedCallback);

		if (m_pRenderer)
		{
			m_pRenderer->SetRenderWindow(m_pRW);
			m_pRenderer->SetResourceManager(m_pRM);
			m_pRenderer->Initialize();

			// Initialize Text manager
			oakvr::core::Text::GetInstance().SetResourceManagerPtr(m_pRM);
			oakvr::core::Text::GetInstance().SetRendererPtr(m_pRenderer);
		}
		Console();
		m_timer.Reset();
		return true;
	}

	void OakVR::Cleanup()
	{
		m_pRenderer->Cleanup();
	}

	// --------------------------------------------------------------------------------
	bool OakVR::Update()
	{
		m_timer.Tick();
		return Update(m_timer.GetDeltaTime());
	}

	// --------------------------------------------------------------------------------
	void OakVR::DrawMeshBoundingBoxes()
	{

	}

	void OakVR::RegisterUpdatable(sp<oakvr::Updatable> pUpdatable)
	{
		m_pUpdatables.push_back(pUpdatable);
	}

	void OakVR::UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable)
	{
		auto size = m_pUpdatables.size();
		m_pUpdatables.erase(std::remove_if(std::begin(m_pUpdatables), std::end(m_pUpdatables), [&](const sp<Updatable> &pRegisteredUpdatable)->bool{ return pRegisteredUpdatable == pUpdatable; }), m_pUpdatables.end());
		if (size == m_pUpdatables.size())
		{
			Log::Error("Trying to unregister an Updatable that was not registered! But how can this be?!... ");
		}
	}

	

	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------
	// core interface
	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------

	auto OakVR::RegisterSubFolderPaths(const std::string &path)->bool
	{
		return m_pRM->AddPathsFromFolder(path);
	}

	sp<oakvr::core::MemoryBuffer> OakVR::GetResource(const std::string &id)
	{
		return m_pRM->GetResource(id);
	}

	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------
	// lifecycle
	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------
	bool oakvrInit(std::vector<std::string> cmdLine)
	{
		for (auto e : OakVR::GetInstance().m_engineInitializers)
		{
			e();
		}

		for (auto e : OakVR::GetInstance().m_userInitializers)
		{
			e();
		}

		return true;
	}

	// --------------------------------------------------------------------------------
	bool oakvrUpdate()
	{
		PROFILER_FUNC_SCOPED_TIMER;
		return OakVR::GetInstance().Update();
	}

	// --------------------------------------------------------------------------------
	void oakvrExit()
	{
		OakVR::GetInstance().Cleanup();
		Log::Info("OakVR shutting down!\n");

	}
}	// namespace oakvr
