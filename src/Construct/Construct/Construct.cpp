#include "Construct.h"

#include "OakVR/OakVR.h"

#include "Input/KeyboardInput/KeyboardInput.h"
#include "Input/MouseInput/MouseInput.h"
#include "Text/Text.h"
#include "Log/Log.h"
#include "Math/Matrix.h"

#include "FreeCamera.h"

namespace construct
{
	Construct::Construct()
	{
		oakvr::Log::SetMaxLevel(oakvr::Log::LogLevel::info);

		oakvr::render::SetRenderWindowPosition(200, 100);
		oakvr::render::SetRenderWindowSize(1024, 768);
		oakvr::render::SetRenderWindowTitle("Construct with Oak VR");

		oakvr::core::RegisterSubFolderPaths("D:/Projects/OakVR/resources");
		
		// load up some fonts
		oakvr::core::AddFontFace("Tinos-Regular");
		oakvr::core::AddFontFace("FiraSans-Light");
		oakvr::core::AddFontFace("FiraMono-Regular");

		auto pCamera = std::make_shared<oakvr::render::Camera>("rotating_camera", oakvr::math::Vector3{ 0.f, 1.f, 25.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(90.f), oakvr::render::GetRenderWindowWidth() / oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("panning_camera", oakvr::math::Vector3{ 0.f, 1.f, 25.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(90.f), oakvr::render::GetRenderWindowWidth() / oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("static_camera", oakvr::math::Vector3{ 0.f, 1.f, 25.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(90.f), oakvr::render::GetRenderWindowWidth() / oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<FreeCamera>("free_camera", oakvr::math::Vector3{ 0.f, 1.f, 25.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f }, 10.f, 1.f);
		pCamera->SetPerspectiveProjection(oakvr::math::DegreesToRadians(90.f), oakvr::render::GetRenderWindowWidth() / oakvr::render::GetRenderWindowHeight(), 1.f, 1000.f);
		oakvr::render::RegisterCamera(pCamera);
		oakvr::render::SetCurrentCamera(pCamera);


		pCamera = std::make_shared<FreeCamera>("orthographic_camera", oakvr::math::Vector3{ 0.f, 1.f, 25.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f }, 10.f, 1.f);
		float aspect = oakvr::render::GetRenderWindowWidth() / oakvr::render::GetRenderWindowHeight();
		pCamera->SetOrthographicProjection(aspect * 10, 10, 1, 1000);
		oakvr::render::RegisterCamera(pCamera);

		CreateTestMesh1();
		CreateTestMesh2();
		CreateTestMesh3();
		CreateTestMeshRoom();
	}

	void Construct::Update(float dt)
	{
		if (oakvr::render::RenderWindowHasFocus())
		{
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::y))
				oakvr::render::DrawText("Y key is down", oakvr::math::Vector3(-0.9f, 15.9f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
			if (oakvr::input::keyboard::IsDown(oakvr::input::Key::b))
				oakvr::render::DrawText("B key is down again", oakvr::math::Vector3(-30.1f, 10.9f, -20.f), oakvr::render::Color::Yellow, "Fira Sans Light");
			if (oakvr::input::mouse::IsLeftButtonDown())
				oakvr::render::DrawText("Left mouse button down", oakvr::math::Vector3(-30.9f, 5.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");

			if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_1))
				oakvr::render::SetCurrentCamera("static_camera");
			else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_2))
				oakvr::render::SetCurrentCamera("rotating_camera");
			else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_3))
				oakvr::render::SetCurrentCamera("panning_camera");
			else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_4))
				oakvr::render::SetCurrentCamera("free_camera");
			else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_5))
				oakvr::render::SetCurrentCamera("orthographic_camera");
		}

		static float accumulatedTime = 0.f;
		static std::string str = "FPS: " + std::to_string(static_cast<int>(dt > 1e-9f ? 1.f / dt : 0.f));
		if ((accumulatedTime += dt) > 0.3f)
		{
			accumulatedTime = 0.f;
			str = "FPS: " + std::to_string(static_cast<int>(dt > 1e-9f ? 1.f / dt : 0.f));
		}
		oakvr::render::DrawText(str, oakvr::math::Vector3(-10.f, -25.f, -20.f), oakvr::render::Color::Yellow, "Fira Mono Regular");

		oakvr::render::DrawLine({ -5.f, 0.f, 0.f }, { 5.f, 0.f, 0.f }, 0.1f, oakvr::render::Color::Red, oakvr::render::Color::White);
		oakvr::render::DrawLine({ 0.f, 0.f, -5.f }, { 0.f, 0.f, 5.f }, 0.1f, oakvr::render::Color::Blue, oakvr::render::Color::White);
		oakvr::render::DrawLine({ 0.f, -5.f, 0.f }, { 0.f, 5.f, 0.f }, 0.1f, oakvr::render::Color::Green, oakvr::render::Color::White);
		
		//auto pCamera = oakvr::render::GetCamera("rotating_camera");
		//if (pCamera)
		//	pCamera->Rotate(0, -dt, 0);
		//pCamera = oakvr::render::GetCamera("panning_camera");
	//	if(pCamera)
		//	pCamera->Translate(0, dt * 0.2f, 0);
		auto pCamera = oakvr::render::GetCamera("free_camera");
		if (pCamera)
			pCamera->Update(dt);


		auto pMesh = oakvr::render::GetMesh("TestCube");
		auto matWorld = pMesh->GetWorldMatrix();
		pMesh->SetWorldMatrix(matWorld * oakvr::math::Matrix::RotationY(dt * oakvr::math::PiOverTwelve));

		pMesh = oakvr::render::GetMesh("monkey1");
		matWorld = pMesh->GetWorldMatrix();
		pMesh->SetWorldMatrix(matWorld * oakvr::math::Matrix::RotationY(dt * oakvr::math::PiOverSix));

		pMesh = oakvr::render::GetMesh("monkey2");
		matWorld = pMesh->GetWorldMatrix();
		pMesh->SetWorldMatrix(matWorld * oakvr::math::Matrix::RotationX(dt * oakvr::math::PiOverSix));
		
	}

	void Construct::CreateTestMesh1()
	{
		// build a test mesh
		std::vector<oakvr::render::VertexElementDescriptor> ved{
			oakvr::render::VertexElementDescriptor::Semantic::position,
			oakvr::render::VertexElementDescriptor::Semantic::tex_coord,
			//{ 12, oakvr::render::VertexElementDescriptor::Semantic::color }
		};

		oakvr::core::MemoryBuffer vb{ 8 * ComputeVertexStride(ved) * sizeof(float) };
		oakvr::core::MemoryBuffer ib{ 6 * 2 * 3 * sizeof(uint32_t) };
		float pVertices[] = {
			1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			3.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			3.0f, 1.0f, 3.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 3.0f, 0.0f, 1.0f,

			1.0f, 3.0f, 1.0f, 1.0f, 0.0f,
			3.0f, 3.0f, 1.0f, 1.0f, 1.0f,
			3.0f, 3.0f, 3.0f, 0.0f, 1.0f,
			1.0f, 3.0f, 3.0f, 0.0f, 0.0f 
		};

		uint32_t pIndices[] = {
			0, 1, 2,
			0, 2, 3,
			1, 6, 2,
			1, 5, 6,

			0, 5, 1,
			0, 4, 5,
			4, 6, 5,
			4, 7, 6,

			2, 7, 3,
			2, 6, 7,
			3, 4, 0,
			3, 7, 4
		};

		memcpy(vb.GetDataPtr(), pVertices, vb.Size());
		memcpy(ib.GetDataPtr(), pIndices, ib.Size());

		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");

		auto pMesh = oakvr::render::CreateMesh("TestCube", ved, vb, 4, ib, pMaterial, { "oakvr" });
		pMesh->SetWorldMatrix(oakvr::math::Matrix::RotationZ(oakvr::math::PiOverTwo));
	}

	void Construct::CreateTestMesh2()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("DefaultColor");
		auto pMesh = oakvr::render::CreateMesh("monkey1", "monkeymesh", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Translation(1,2,3));
	}

	void Construct::CreateTestMesh3()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");
		auto pMesh = oakvr::render::CreateMesh("monkey2", "monkeymesh", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Translation(-1, 2, 3));
	}

	void Construct::CreateTestMeshRoom()
	{
		auto pMaterial = std::make_shared<oakvr::render::Material>("Default");
		auto pMesh = oakvr::render::CreateMesh("room", "roommesh", pMaterial);
		pMesh->SetWorldMatrix(oakvr::math::Matrix::Scale(25));
	}

	void InitializeConstruct()
	{
		oakvr::RegisterUpdateable(std::make_shared<Construct>());
	}

	OAKVR_REGISTER_INITIALIZER(InitializeConstruct)
}