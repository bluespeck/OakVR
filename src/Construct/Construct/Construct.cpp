#include "Construct.h"

#include "OakVR/OakVR.h"

#include "Input/KeyboardInput/KeyboardInput.h"
#include "Input/MouseInput/MouseInput.h"
#include "Text/Text.h"

namespace construct
{
	Construct::Construct()
	{
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

	void Construct::Update(double dt)
	{
		if (oakvr::input::keyboard::IsDown(oakvr::input::Key::a))
			oakvr::core::Text::GetInstance().RenderText("AAAAAAAAAAAAAAA!", oakvr::math::Vector3(0.f, 0.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
		else if (oakvr::input::keyboard::IsDown(oakvr::input::Key::b))
			oakvr::core::Text::GetInstance().RenderText("BBBBBBBBBBBBBBB!", oakvr::math::Vector3(0.f, 0.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
		else if (oakvr::input::mouse::IsLeftButtonDown())
			oakvr::core::Text::GetInstance().RenderText("MouseMouse!", oakvr::math::Vector3(0.f, 0.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
		else
			oakvr::core::Text::GetInstance().RenderText("This is a test!", oakvr::math::Vector3(0.f, 0.f, -20.f), oakvr::render::Color::Yellow, "Tinos Regular");
	}

	void InitializeConstruct()
	{
		oakvr::RegisterUpdateable(std::make_shared<Construct>());
	}

	OAKVR_REGISTER_INITIALIZER(InitializeConstruct)
}