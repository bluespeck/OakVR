#include "OakVR.h"
#include "OakVR/VisualComponent.h"
#include "OakVR/TransformComponent.h"
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
	void OakVR::UpdateThread()
	{
		while (true)
		{
			WaitForUpdateFrameStart();

			m_timer.Tick();
			Update(m_timer.GetDeltaTime());

			NotifyUpdateFrameFinished();
		}
	}

	void OakVR::RenderThread()
	{
		while (true)
		{
			WaitForRenderFrameStart();
			
			Render();
			
			NotifyRenderFrameFinished();
		}
	}

	void OakVR::WaitForUpdateFrameStart()
	{
		auto ul = std::unique_lock<std::mutex>(m_updateMutex);

		do
		{
			m_updateFrameCanStartCondVar.wait(ul, [this]()->bool {
				return m_updateFrameCanStart;
			});
		} while (!m_updateFrameCanStart);

		m_updateFrameCanStart = false;
	}

	void OakVR::WaitForRenderFrameStart()
	{
		auto ul = std::unique_lock<std::mutex>(m_renderMutex);

		do
		{
			m_renderFrameCanStartCondVar.wait(ul, [this]()->bool {
				return m_renderFrameCanStart;
			});
		} while (!m_renderFrameCanStart);

		m_renderFrameCanStart = false;
	}

	void OakVR::WaitForUpdateFrameEnd()
	{
		auto ul = std::unique_lock<std::mutex>(m_updateMutex);

		do
		{
			m_updateFrameFinishedCondVar.wait(ul, [this]()->bool {
				return m_updateFrameFinished;
			});
		} while (!m_updateFrameFinished);

		m_updateFrameFinished = false;
	}

	void OakVR::WaitForRenderFrameEnd()
	{
		auto ul = std::unique_lock<std::mutex>(m_renderMutex);

		do
		{
			m_renderFrameFinishedCondVar.wait(ul, [this]()->bool {
				return m_renderFrameFinished;
			});
		} while (!m_renderFrameFinished);

		m_renderFrameFinished = false;
	}

	void OakVR::NotifyUpdateFrameCanStart()
	{
		auto ul = std::unique_lock<std::mutex>(m_updateMutex);

		m_updateFrameCanStart = true;
		m_updateFrameCanStartCondVar.notify_all();
		
	}

	void OakVR::NotifyRenderFrameCanStart()
	{
		auto ul = std::unique_lock<std::mutex>(m_renderMutex);

		m_renderFrameCanStart = true;
		m_renderFrameCanStartCondVar.notify_all();
	}

	void OakVR::NotifyUpdateFrameFinished()
	{
		auto ul = std::unique_lock<std::mutex>(m_updateMutex);

		m_updateFrameFinished = true;
		m_updateFrameFinishedCondVar.notify_all();
	}

	void OakVR::NotifyRenderFrameFinished()
	{
		auto ul = std::unique_lock<std::mutex>(m_renderMutex);

		m_renderFrameFinished = true;
		m_renderFrameFinishedCondVar.notify_all();
	}

	// --------------------------------------------------------------------------------
	auto OakVR::Update(TimeDeltaType dt) -> bool
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


			// Update step
			// Keep Updatables from interfering with the Updatables vector while they are updated
			// there is a problem with deleting Updatables while the loop is under way in that deleted objects might
			// have Update called for them
			auto pUpdatables = m_pUpdatables;
			for (auto &e : pUpdatables)
				if (!e->Update(dt))
					return false;

			// Render step
			auto pCamera = GetCurrentCamera();
			
			if (pCamera)
			{	
				m_pRenderer->SetCurrentCamera(pCamera);
				m_pRenderer->SetViewMatrix(pCamera->ComputeViewMatrix());
				m_pRenderer->SetProjMatrix(pCamera->GetProjMatrix());

				auto vecMeshes = FrustumCull();
			}
			RegisterObjectsAsRenderables(GetAllObjects());
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

	auto OakVR::Render() -> bool
	{
		m_pRenderer->Render();
		return true;
	}

	auto OakVR::DrawObjects(const ObjectVector &objects) const noexcept -> void
	{
		for (const auto &obj : objects)
		{
			auto visualComponent = obj->GetComponent<oakvr::VisualComponent>();
			if (visualComponent)
			{
				auto transformComponent = obj->GetComponent<oakvr::TransformComponent>();
				auto transform = oakvr::math::Matrix::Identity;
				if (transformComponent)
				{
					transform = oakvr::math::Matrix::Translation(transformComponent->GetPosition()) *
						oakvr::math::Matrix::Scale(transformComponent->GetScale());
					//TODO: * oakvr::math::Matrix::RotationAxisRightHanded(transformComponent->GetOrientation())
				}
				m_pRenderer->RegisterRenderable(visualComponent->GetMesh(), transform);
			}
		}
	}

	auto OakVR::RegisterObjectsAsRenderables(const ObjectVector  &objects) const noexcept -> void
	{
		m_pRenderer->UnregisterAllRenderables();

		for (const auto &obj : objects)
		{
			auto visualComponent = obj->GetComponent<oakvr::VisualComponent>();
			if (visualComponent)
			{
				auto transformComponent = obj->GetComponent<oakvr::TransformComponent>();
				auto transform = oakvr::math::Matrix::Identity;
				if (transformComponent)
				{
					transform = oakvr::math::Matrix::Translation(transformComponent->GetPosition()) *
						oakvr::math::Matrix::Scale(transformComponent->GetScale());
						//TODO: * oakvr::math::Matrix::RotationAxisRightHanded(transformComponent->GetOrientation())
				}
				m_pRenderer->RegisterRenderable(visualComponent->GetMesh(), transform);
			}
		}
	}

	auto OakVR::FrustumCull() -> ObjectVector
	{
		//auto const &vecObjects = GetAllObjects();
		//ObjectVector vecCulledObjects;
		//for (auto &pObj : vecObjects)
		{
//			auto pVisualComp = oakvr::VisualComponent::AsVisualComponent(pObj->GetComponent("Visual"));
			
			//if (pVisualComp->GetMesh()->)

		}

		return {};
		
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

	auto WindowSizeChangedCallback(void *pNativeHandler, int width, int height) -> void
	{
		oakvr::OakVR::GetInstance().OnWindowSizeChanged(pNativeHandler, width, height);
	}

	auto WindowFocusChangedCallback(void *pNativeHandler, int focused) -> void
	{
		oakvr::OakVR::GetInstance().OnWindowFocusChanged(pNativeHandler, focused);
	}

	auto WindowPositionChangedCallback(void *pNativeHandler, int x, int y) -> void
	{
		oakvr::OakVR::GetInstance().OnWindowPositionChanged(pNativeHandler, x, y);
	}

	// --------------------------------------------------------------------------------
	// callback functions end
	// --------------------------------------------------------------------------------


	// --------------------------------------------------------------------------------
	auto OakVR::Initialize() -> bool
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

		{
			m_updateFrameCanStart = true;
			auto updateThread = std::thread(&OakVR::UpdateThread, this);
			updateThread.detach();
		}
		{
			m_renderFrameCanStart = true;
			auto renderThread = std::thread(&OakVR::RenderThread, this);
			renderThread.detach();
		}
		return true;
	}

	auto OakVR::Cleanup() -> void
	{
		m_pRenderer->Cleanup();
	}

	// --------------------------------------------------------------------------------
	auto OakVR::Update() -> bool
	{
		NotifyUpdateFrameCanStart();
		NotifyRenderFrameCanStart();

		WaitForUpdateFrameEnd();
		WaitForRenderFrameEnd();

		m_pRenderer->SwapBuffers();

		return true;
	}

	// --------------------------------------------------------------------------------
	auto OakVR::DrawMeshBoundingBoxes() -> void
	{

	}

	auto OakVR::RegisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void
	{
		m_pUpdatables.push_back(pUpdatable);
	}

	auto OakVR::UnregisterUpdatable(sp<oakvr::Updatable> pUpdatable) -> void
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

	auto OakVR::GetResource(const std::string &id) -> sp<oakvr::core::MemoryBuffer>
	{
		return m_pRM->GetResource(id);
	}

	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------
	// lifecycle
	// --------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------
	auto oakvrInit(std::vector<std::string> cmdLine) -> bool
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
	auto oakvrUpdate() -> bool
	{
		PROFILER_FUNC_SCOPED_TIMER;
		return OakVR::GetInstance().Update();
	}

	// --------------------------------------------------------------------------------
	auto oakvrExit() -> void
	{
		OakVR::GetInstance().Cleanup();
		Log::Info("OakVR shutting down!\n");

	}
}	// namespace oakvr
