#include "Construct.h"

#include "OakVR/OakVR.h"

#include "Input/KeyboardInput/KeyboardInput.h"
#include "Input/MouseInput/MouseInput.h"
#include "Text/Text.h"

namespace construct
{
	Construct::Construct()
	{
		oakvr::core::RegisterSubFolderPaths("D:/Projects/OakVR/resources");
		
		// load up some fonts
		oakvr::core::AddFontFace("Tinos-Regular");
		oakvr::core::AddFontFace("FiraSans-Light");
		oakvr::core::AddFontFace("FiraMono-Regular");

		auto pCamera = std::make_shared<oakvr::render::Camera>("rotating_camera", oakvr::math::Vector3{ 0.f, 0.f, -5.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		oakvr::render::RegisterCamera(pCamera);
		oakvr::render::SetCurrentCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("panning_camera", oakvr::math::Vector3{ 0.f, 0.f, -2.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		oakvr::render::RegisterCamera(pCamera);

		pCamera = std::make_shared<oakvr::render::Camera>("static_camera", oakvr::math::Vector3{ 0.f, 0.f, -2.f }, oakvr::math::Vector3{ 0.f, 0.f, 0.f }, oakvr::math::Vector3{ 0.f, 1.f, 0.f });
		oakvr::render::RegisterCamera(pCamera);

		CreateTestMesh();


	}

	void Construct::Update(double dt)
	{
		if (oakvr::input::keyboard::IsDown(oakvr::input::Key::a))
			oakvr::render::DrawText("A key is down", oakvr::math::Vector3(-0.9f, 15.9f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
		if (oakvr::input::keyboard::IsDown(oakvr::input::Key::b))
			oakvr::render::DrawText("B key is down again", oakvr::math::Vector3(-30.1f, 10.9f, -20.f), oakvr::render::Color::Yellow, "Fira Sans Light");
		if (oakvr::input::mouse::IsLeftButtonDown())
			oakvr::render::DrawText("Left mouse button down", oakvr::math::Vector3(-30.9f, 5.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
		
		oakvr::render::DrawText("~'_abcdef01259`!", oakvr::math::Vector3(-10.f, -25.f, -20.f), oakvr::render::Color::Yellow, "Fira Mono Regular");

		if (oakvr::input::keyboard::IsPressed(oakvr::input::Key::_1))
			oakvr::render::SetCurrentCamera("static_camera");
		else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_2))
			oakvr::render::SetCurrentCamera("rotating_camera");
		else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::_3))
			oakvr::render::SetCurrentCamera("panning_camera");

		auto pCamera = oakvr::render::GetCamera("rotating_camera");
		if (pCamera)
			pCamera->Rotate(0, -dt, 0);
		pCamera = oakvr::render::GetCamera("panning_camera");
		if (pCamera)
		{
			pCamera->Translate(0, dt * 0.2f, 0);
		}

	}

	void Construct::CreateTestMesh()
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
			-1.f, -1.f, -1.f, 1.f, 0.f,// 0.5, 0.5, 0.5,
			1.0f, -1.f, -1.f, 1.f, 1.f,// 0.5, 0.5, 0.5,
			1.0f, -1.f, 1.0f, 1.f, 0.f,// 0.5, 0.5, 0.5,
			-1.f, -1.f, 1.0f, 1.f, 1.f,// 0.5, 0.5, 0.5,

			-1.f, 1.0f, -1.f, 0.f, 0.f,// 0.5, 0.5, 0.5,
			1.0f, 1.0f, -1.f, 0.f, 1.f,// 0.5, 0.5, 0.5,
			1.0f, 1.0f, 1.0f, 1.f, 1.f,// 0.5, 0.5, 0.5,
			-1.f, 1.0f, 1.0f, 0.f, 1.f // 0.5, 0.5, 0.5
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

		auto pMaterial = std::make_shared<oakvr::render::Material>(std::string("Default"));

		oakvr::render::CreateMesh(ved, vb, 4, ib, pMaterial, { "oakvr" });
		oakvr::render::RegisterShader("Default");
	}

	void InitializeConstruct()
	{
		oakvr::RegisterUpdateable(std::make_shared<Construct>());
	}

	OAKVR_REGISTER_INITIALIZER(InitializeConstruct)
}