#include "Construct.h"

#include "OakVR/OakVR.h"
#include "OakVR/TransformComponent.h"
#include "OakVR/VisualComponent.h"

#include "Input/KeyboardInput/KeyboardInput.h"
#include "Input/MouseInput/MouseInput.h"
#include "Text/Text.h"
#include "Log/Log.h"
#include "Math/Matrix.h"

#include "FreeCamera.h"

#include "Profiler/Profiler.h"

namespace construct
{
	Construct::Construct()
	{
		oakvr::Log::SetMaxLevel(oakvr::Log::LogLevel::info);

		oakvr::render::SetRenderWindowPosition(0, 100);
		oakvr::render::SetRenderWindowSize(1200, 900);
		oakvr::render::SetRenderWindowTitle("Construct with Oak VR");

		oakvr::core::RegisterSubFolderPaths("E:/Projects/OakVR/resources");
		
		// load up some fonts
		oakvr::core::AddFontFace("Tinos-Regular");
		oakvr::core::AddFontFace("FiraSans-Light");
		oakvr::core::AddFontFace("FiraMono-Regular");
		oakvr::core::AddFontFace("NotoSans-Bold");

		auto pCamera = std::make_shared<oakvr::render::Camera>("rotating_camera", oakvr::math::Vector3{ 0.f, 0.f, 50.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(60.f), oakvr::render::GetRenderWindowWidth() , oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("panning_camera", oakvr::math::Vector3{ 0.f, 0.f, 50.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(60.f), oakvr::render::GetRenderWindowWidth() , oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("static_camera", oakvr::math::Vector3{ 0.f, 0.f, 50.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(60.f), oakvr::render::GetRenderWindowWidth() , oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<FreeCamera>("free_camera", oakvr::math::Vector3{ 0.f, 0.f, 50.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f }, 10.f, 1.f);
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(60.f), oakvr::render::GetRenderWindowWidth() , oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);
		oakvr::render::SetCurrentCamera(pCamera);
		
		pCamera = std::make_shared<FreeCamera>("orthographic_camera", oakvr::math::Vector3{ 0.f, 0.f, -50.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f }, 10.f, 1.f);
		pCamera->SetOrthographicProjection(oakvr::render::GetRenderWindowWidth(), oakvr::render::GetRenderWindowHeight(), 10, 2000);
		oakvr::render::RegisterCamera(pCamera);

		CreateTestMesh1();
		CreateTestMesh2();
		CreateTestMesh3();
		CreateTestMesh4();
		CreateTestMeshRoom();
	}

	const int meshNum = 2;
	auto Construct::Update(float dt)->bool
	{
		static float fovValue = 0.f;
		if (oakvr::render::RenderWindowHasFocus() && !oakvr::input::keyboard::GetCaptor())
		{
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::y))
				oakvr::render::DrawText("Y key is down", oakvr::math::Vector3(-1.f, 1.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular", 8);
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::b))
				oakvr::render::DrawText("B key is down again", oakvr::math::Vector3(-30.1f, 100.9f, -20.f), oakvr::render::Color::Yellow, "Fira Sans Light", 20);
			if (oakvr::input::mouse::IsLeftButtonDown())
				oakvr::render::DrawText("Left mouse button down", oakvr::math::Vector3(-30.9f, 25.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular", 20);

			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_1))
				oakvr::render::SetCurrentCamera("static_camera");
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_2))
				oakvr::render::SetCurrentCamera("rotating_camera");
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_3))
				oakvr::render::SetCurrentCamera("panning_camera");
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_4))
				oakvr::render::SetCurrentCamera("free_camera");
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_5))
				oakvr::render::SetCurrentCamera("orthographic_camera");
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::f5))
				oakvr::render::ToggleWireframe();
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::f6))
				oakvr::render::ToggleCulling();
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::f7))
				oakvr::render::ToggleDepthTest();
			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::f8))
				oakvr::render::ToggleBlending();

			
			auto pCamera = oakvr::render::GetCurrentCamera();
			if (pCamera)
			{
				fovValue = oakvr::math::RadiansToDegrees(2.f * atan(1.f/pCamera->GetProjMatrix()._22));
				if (oakvr::input::keyboard::IsDown(oakvr::input::Key::lBracket_curly))
				{
					fovValue -= 0.5f;
					pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(fovValue), oakvr::render::GetRenderWindowHeight() / oakvr::render::GetRenderWindowWidth(), 1.f, 1000.f);
				}
				if (oakvr::input::keyboard::IsDown(oakvr::input::Key::rBracket_curly))
				{
					fovValue += 0.5f;
					pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(fovValue), oakvr::render::GetRenderWindowHeight() / oakvr::render::GetRenderWindowWidth(), 1.f, 1000.f);
				}
			}
		}

		static float accumulatedTime = 0.f;
		static std::string str = "FPS: " + std::to_string(static_cast<int>(dt > 1e-9f ? 1.f / dt : 0.f));
		if ((accumulatedTime += dt) > 0.3f)
		{
			accumulatedTime = 0.f;
			str = "FPS: " + std::to_string(static_cast<int>(dt > 1e-9f ? 1.f / dt : 0.f));
		}
		oakvr::render::DrawText(str, oakvr::math::Vector3(1.f, 0.f, 1.f), oakvr::render::Color::Yellow, "Fira Mono Regular", 0.2f);
		oakvr::render::DrawText(
			"Fov" + std::to_string(static_cast<int>(fovValue))
			+ " C" + std::to_string(oakvr::render::IsCullingEnabled())
			+ " D" + std::to_string(oakvr::render::IsDepthTestEnabled())
			+ " B" + std::to_string(oakvr::render::IsBlendingEnabled())
			, oakvr::math::Vector3(0.f, 100.f, 0.f), oakvr::render::Color::Yellow, "Fira Mono Regular", 5);
		
		/*auto vec = oakvr::profiler::Profiler::GetInstance().GetSortedProfilingData();
		float fIndex = 0.0f;
		for (auto elem : vec)
		{
			auto &pd = elem.second;
			auto percentage = static_cast<int>(static_cast<float>(pd.totalTime) / static_cast<float>(vec.front().second.totalTime) * 100.0f);
			char line[512];
			sprintf(line, "%60s -- [%%]=%3d h=%-6lu total[ms]=%-9llu lst[us]=%-9llu max[us]=%-9llu avg[us]=%-9llu", pd.id.name.c_str(), percentage, pd.hits, pd.totalTime / 1000, pd.latestTime, pd.maxTime, pd.avgTime);
			oakvr::render::DrawText(std::string(line), oakvr::math::Vector3(-50.f, -fIndex, -20.f), oakvr::render::Color::Yellow, "Noto Sans Bold");
			fIndex += 3.0f;
		}*/

		oakvr::render::DrawLine({ -10.f, 0.f, 0.f }, { 10.f, 0.f, 0.f }, 0.1f, oakvr::render::Color::Red, oakvr::render::Color::White);
		oakvr::render::DrawLine({ 0.f, -10.f, 0.f }, { 0.f, 10.f, 0.f }, 0.1f, oakvr::render::Color::Green, oakvr::render::Color::White);
		oakvr::render::DrawLine({ 0.f, 0.f, -10.f }, { 0.f, 0.f, 10.f }, 0.1f, oakvr::render::Color::Blue, oakvr::render::Color::White);
		
		
		auto pCamera = oakvr::render::GetCurrentCamera();
		if (pCamera)
			pCamera->Update(dt);
		
		if (oakvr::input::keyboard::IsHeld(oakvr::input::Key::t))
			oakvr::render::TransformMesh("TestCube", oakvr::math::Matrix::RotationY(dt * oakvr::math::PiOverSix));
		else if (oakvr::input::keyboard::IsHeld(oakvr::input::Key::r))
			oakvr::render::TransformMesh("TestCube", oakvr::math::Matrix::RotationY(dt * -oakvr::math::PiOverSix));
		
		/*
		// update the marix of spinning monkeys
		for (int i = -meshNum; i < meshNum; ++i)
		{
			for (int j = -meshNum; j < meshNum; ++j)
			{
				oakvr::render::TransformMesh("monkey" + std::to_string(i) + std::to_string(j), oakvr::math::Matrix::RotationX(dt * i / meshNum * j / meshNum * oakvr::math::PiOverSix));
			}
		}
		*/
		oakvr::render::TransformMesh("monkey2", oakvr::math::Matrix::RotationX(-dt * oakvr::math::PiOverTwo));
		
		return true;
	}

	void Construct::CreateTestMesh1()
	{
		// build a test mesh
		std::vector<oakvr::render::VertexElementDescriptor> ved{
			oakvr::render::VertexElementDescriptor::Semantic::position,
			oakvr::render::VertexElementDescriptor::Semantic::tex_coord,
		};

		oakvr::core::MemoryBuffer vb{ 24 * ComputeVertexStride(ved) };
		oakvr::core::MemoryBuffer ib{ 6 * 2 * 3 * sizeof(uint32_t) };
		float pVertices[] = {
			-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, 1.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, 1.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

			-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		uint32_t pIndices[] = {
			0 +  0, 1 +  0, 3 +  0,
			3 +  0, 1 +  0, 2 +  0,
			7 +  0, 6 +  0, 4 +  0,
			4 +  0, 6 +  0, 5 +  0,

			7 +  8, 4 +  8, 3 +  8,
			3 +  8, 4 +  8, 0 +  8,
			5 +  8, 6 +  8, 1 +  8,
			1 +  8, 6 +  8, 2 +  8,

			4 + 16, 5 + 16, 0 + 16,
			0 + 16, 5 + 16, 1 + 16,
			6 + 16, 7 + 16, 2 + 16,
			2 + 16, 7 + 16, 3 + 16
			
		};

		memcpy(vb.GetDataPtr(), pVertices, vb.Size());
		memcpy(ib.GetDataPtr(), pIndices, ib.Size());

		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");

		auto pMesh = oakvr::render::CreateMesh("TestCube", ved, vb, sizeof(uint32_t), ib, pMaterial, { "oakvr" });
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Translation(0, 0, 0) * oakvr::math::Matrix::Scale(1));

		auto pObj = oakvr::OakVR::GetInstance().CreateObject("TestCube");
		auto pTransformComp = pObj->AddComponent<oakvr::TransformComponent>();
		pTransformComp->SetPosition({ 0, 0, 0 });

		auto pVisualComp = pObj->AddComponent<oakvr::VisualComponent>();
		pVisualComp->SetMeshFromResource("TestCube");
		// updating the world matrix for the mesh should be done by the parent object 
		// when it detects that the translation component changed in the current frame
		pVisualComp->GetMesh()->SetWorldMatrix(oakvr::math::Matrix::Translation(pTransformComp->GetPosition()));
		
		// Add object to scene
		oakvr::OakVR::GetInstance().AddObjectToGraph(pObj, "root");

		

		// On engine update do a filter on the objects


		// based on frustum intersection (use BSpheres)
		// Further parse the structure and batch geometries based on material
		// Create vertex/index buffers for batches
		// 




	}

	void Construct::CreateTestMesh2()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("DefaultColor");
		auto pMesh = oakvr::render::CreateMesh("monkey", "monkeymesh", pMaterial);
		

		for (int i = -meshNum; i < meshNum; ++i)
		{
			for (int j = -meshNum; j < meshNum; ++j)
			{
				auto pObj = oakvr::OakVR::GetInstance().CreateObject("monkey_" + std::to_string(i) + "_" + std::to_string(j));
				auto pTransformComp = pObj->AddComponent<oakvr::TransformComponent>();
				pTransformComp->SetPosition({ 0, 0, 0 });

				auto pVisualComp = pObj->AddComponent<oakvr::VisualComponent>();
				pVisualComp->SetMeshFromResource("monkey");
				// updating the world matrix for the mesh should be done by the parent object 
				// when it detects that the translation component changed in the current frame
				pVisualComp->GetMesh()->SetWorldMatrix(oakvr::math::Matrix::Translation(static_cast<float>(i * 3), static_cast<float>(j * 3), 3.0f)* oakvr::math::Matrix::Scale(30));

				// Add object to scene
				oakvr::OakVR::GetInstance().AddObjectToGraph(pObj, "root");

			}
		}
	}

	void Construct::CreateTestMesh3()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");
		auto pMesh = oakvr::render::CreateMesh("monkey2", "monkeymesh", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Scale(250) * oakvr::math::Matrix::Translation(1, 1, 1));
	}

	void Construct::CreateTestMesh4()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");
		auto pMesh = oakvr::render::CreateMesh("sphere1", "sphere", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Scale(1) * oakvr::math::Matrix::Translation(1, 1, 1));

		auto pObj = oakvr::OakVR::GetInstance().CreateObject("sphere1");
		auto pTransformComp = pObj->AddComponent<oakvr::TransformComponent>();
		pTransformComp->SetPosition({ 5, 0, 0 });
		pTransformComp->SetScale(3);

		auto pVisualComp = pObj->AddComponent<oakvr::VisualComponent>();
		pVisualComp->SetMeshFromResource("sphere1");

		// Add object to scene
		oakvr::OakVR::GetInstance().AddObjectToGraph(pObj, "root");
	}

	void Construct::CreateTestMeshRoom()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");
		auto pMesh = oakvr::render::CreateMesh("room", "roommesh", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Scale(10));

		auto pObj = oakvr::OakVR::GetInstance().CreateObject("room");
		auto pTransformComp = pObj->AddComponent<oakvr::TransformComponent>();
		pTransformComp->SetPosition( 0, 0, 0 );
		pTransformComp->SetScale(5);

		auto pVisualComp = pObj->AddComponent<oakvr::VisualComponent>();
		pVisualComp->SetMeshFromResource("room");
		// updating the world matrix for the mesh should be done by the parent object 
		// when it detects that the translation component changed in the current frame
		
		// Add object to scene
		oakvr::OakVR::GetInstance().AddObjectToGraph(pObj, "root");
	}

	OAKVR_REGISTER_UPDATABLE(Construct)
}