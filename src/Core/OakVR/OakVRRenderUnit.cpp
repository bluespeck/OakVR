#include "OakVR/OakVRRenderUnit.h"

#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RenderWindow.h"
#include "Renderer/Renderer/Shader.h"
#include "Renderer/Renderer/Mesh.h"
#include "Renderer/Renderer/MeshElement.h"
#include "Renderer/Renderer/Material.h"
#include "Renderer/Renderer/Color.h"

#include "CameraManager.h"

#include "Text/Text.h"

#include "Utils/BufferReader.h"

#include "Math/Matrix44.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include "Log/Log.h"
#include "Profiler/Profiler.h"


namespace oakvr
{
		OakVRRenderUnit::OakVRRenderUnit()
			: m_pRW{ std::make_shared<oakvr::render::RenderWindow>("oakvr", 100, 100, 1024, 768) }
			, m_pRenderer{ std::make_shared<oakvr::render::Renderer>() }
			, m_pCM{ std::make_shared<oakvr::render::CameraManager>() }
		{ 
		}

		auto OakVRRenderUnit::DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const oakvr::render::Color &color) -> void
		{
			PROFILER_FUNC_SCOPED_TIMER;
			DrawLine(start, end, thickness, color, color);
		}

		auto OakVRRenderUnit::DrawLine(const oakvr::math::Vector3 &start, const oakvr::math::Vector3 &end, float thickness, const  oakvr::render::Color &endColor, const oakvr::render::Color &startColor) -> void
		{
			oakvr::math::Vector3 up{ 0, 1, 0 };
			oakvr::math::Vector3 lineDir = end - start;
			oakvr::math::Vector3 p1;
			oakvr::math::Vector3 p2;
			if ((lineDir.GetNormalized() - up).GetLength() > 1e-6f)
			{
				p1 = up.Cross(lineDir).GetNormalized();
			}
			else
			{
				oakvr::math::Vector3 right{ 1, 0, 0 };
				p1 = right.Cross(lineDir).GetNormalized();
			}
			p2 = p1.Cross(lineDir).GetNormalized();
			p1 *= thickness;
			p2 *= thickness;

			std::vector<oakvr::render::VertexElementDescriptor> ved{
				oakvr::render::VertexElementDescriptor::Semantic::position,
				oakvr::render::VertexElementDescriptor::Semantic::color
			};

			oakvr::core::MemoryBuffer vb{ 8 * ComputeVertexStride(ved) };
			oakvr::core::MemoryBuffer ib{ 6 * 2 * 3 * sizeof(uint32_t) };
			struct Vertex
			{
				oakvr::math::Vector3 pos;
				oakvr::math::Vector4 color;
			} pVertices[] = {
				{ start - p1 + p2, startColor },
				{ start - p1 - p2, startColor },
				{ end - p1 - p2, endColor },
				{ end - p1 + p2, endColor },
				{ start + p1 + p2, startColor },
				{ start + p1 - p2, startColor },
				{ end + p1 - p2, endColor },
				{ end + p1 + p2, endColor },
			};

			uint32_t pIndices[] = {
				0, 3, 1,
				1, 3, 2,
				1, 6, 5,
				1, 2, 6,

				1, 4, 0,
				1, 5, 4,
				5, 6, 7,
				5, 7, 4,

				2, 3, 7,
				2, 7, 6,
				0, 7, 3,
				0, 4, 7,
			};

			memcpy(vb.GetDataPtr(), pVertices, vb.Size());
			memcpy(ib.GetDataPtr(), pIndices, ib.Size());

			auto pMaterial = std::make_shared<oakvr::render::Material>(StringId("DefaultColor"));


			auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(ved, vb, static_cast<uint8_t>(sizeof(uint32_t)), ib, pMaterial, std::vector<StringId>());

			auto pMesh = std::make_shared<oakvr::render::Mesh>();
			pMesh->AddMeshElement(pMeshElem);

			m_pRenderer->RegisterOneFrameMesh(pMesh);
			oakvr::render::RegisterShader(pMaterial->m_shaderName);
		}

		// --------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------
		// render interface
		// --------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------

		auto OakVRRenderUnit::CreateMesh(const StringId &name, sp<oakvr::core::MemoryBuffer> pMeshBuffer, sp<oakvr::render::Material> pMaterial)-> sp<oakvr::render::Mesh>
		{
			auto pMesh = std::make_shared<oakvr::render::Mesh>(name);

			if (!pMeshBuffer.get())
			{
				Log::Error("Could not create mesh \"%s\"", name);
				return pMesh;
			}

			auto meshBufferReader = oakvr::core::MakeBufferReader(*pMeshBuffer);
			uint32_t numMeshElements = 0;
			meshBufferReader.Read(numMeshElements);

			// read mesh element offsets in the buffer and sizes in bytes
			std::vector<std::pair<uint32_t, uint32_t>> offsetsAndSizes;
			for (uint32_t i = 0; i < numMeshElements; ++i)
			{
				uint32_t meshElementOffset = 0, meshElementSize = 0;
				meshBufferReader.Read(meshElementOffset);
				meshBufferReader.Read(meshElementSize);
				offsetsAndSizes.emplace_back(meshElementOffset, meshElementSize);
			}

			for (size_t i = 0; i < offsetsAndSizes.size(); ++i)
			{
				meshBufferReader.SetOffset(offsetsAndSizes[i].first);
				uint32_t numVertices, numChannels;
				meshBufferReader.Read(numVertices);
				meshBufferReader.Read(numChannels);

				oakvr::render::VertexDescriptor vertexDescriptor;
				for (size_t j = 0; j < numChannels; ++j)
				{
					oakvr::render::VertexElementDescriptor::Semantic semantic;
					meshBufferReader.Read(semantic);
					vertexDescriptor.emplace_back(semantic);
				}

				oakvr::core::MemoryBuffer vertexBuffer(numVertices * oakvr::render::ComputeVertexStride(vertexDescriptor));
				meshBufferReader.Read(vertexBuffer.GetDataPtr(), vertexBuffer.Size());

				uint32_t numIndices = 0;
				uint32_t indexStride = 0;
				oakvr::render::PrimitiveTopology primitiveTopology = oakvr::render::PrimitiveTopology::ePT_TriangleList;
				meshBufferReader.Read(numIndices);
				meshBufferReader.Read(indexStride);
				meshBufferReader.Read(primitiveTopology);

				oakvr::core::MemoryBuffer indexBuffer(numIndices * indexStride);
				meshBufferReader.Read(indexBuffer.GetDataPtr(), indexBuffer.Size());

				uint32_t numTextures = 0;
				meshBufferReader.Read(numTextures);

				std::vector<StringId> textureNames;
				for (size_t i = 0; i < numTextures; ++i)
				{
					uint32_t nameSize = 0;
					meshBufferReader.Read(nameSize);
					auto pName = std::make_unique<char[]>(nameSize + 1);
					meshBufferReader.Read(pName.get(), nameSize);
					pName.get()[nameSize] = 0;
					auto texName = std::string(pName.get());
					textureNames.push_back(texName.substr(0, texName.length() - 4));
				}

				auto pMeshElem = std::make_shared<oakvr::render::MeshElement>(vertexDescriptor, vertexBuffer, indexStride, indexBuffer, pMaterial, textureNames);
				pMesh->AddMeshElement(pMeshElem);
			}

			return pMesh;
		}

		auto OakVRRenderUnit::RegisterMesh(sp<oakvr::render::Mesh> pMesh) -> void
		{
			m_pRenderer->RegisterMesh(pMesh);
		}

		auto OakVRRenderUnit::GetRegisteredMesh(const StringId &name)->sp < oakvr::render::Mesh >
		{
			return m_pRenderer->GetRegisteredMesh(name);
		}

		auto OakVRRenderUnit::UnregisterMesh(sp<oakvr::render::Mesh> pMesh) -> void
		{
			m_pRenderer->UnregisterMesh(pMesh);
		}


		auto OakVRRenderUnit::TransformMesh(const StringId &meshName, const oakvr::math::Matrix44 &mat) -> void
		{
			auto pMesh = m_pRenderer->GetRegisteredMesh(meshName);
			if (pMesh)
				pMesh->Transform(mat);
		}

		auto OakVRRenderUnit::RegisterShader(StringId shaderName) -> void
		{
			m_pRenderer->RegisterShaderProgram(shaderName);
		}

		auto OakVRRenderUnit::RegisterCamera(sp<oakvr::render::Camera> pCamera) -> void
		{
			m_pCM->RegisterCamera(pCamera);
		}

		auto OakVRRenderUnit::UnregisterCamera(sp<oakvr::render::Camera> pCamera) -> void
		{
			m_pCM->UnregisterCamera(pCamera);
		}

		sp<oakvr::render::Camera> OakVRRenderUnit::GetCamera(const StringId &cameraId)
		{
			return m_pCM->GetCamera(cameraId);
		}

		auto OakVRRenderUnit::GetCurrentCamera()->sp < oakvr::render::Camera >
		{
			return m_pCM->GetCurrentCamera();
		}

		auto OakVRRenderUnit::SetCurrentCamera(sp<oakvr::render::Camera> pCamera) -> void
		{
			m_pCM->SetCurrentCamera(pCamera);
		}

		auto OakVRRenderUnit::SetCurrentCamera(const StringId &cameraId) -> void
		{
			m_pCM->SetCurrentCamera(cameraId);
		}

		auto OakVRRenderUnit::SetRenderWindowPosition(int x, int y) -> void
		{
			m_pRW->SetPosition(x, y);
		}

		auto OakVRRenderUnit::SetRenderWindowSize(unsigned int width, unsigned int height) -> void
		{
			m_pRW->SetSize(width, height);
		}

		auto OakVRRenderUnit::GetRenderWindowSize()const->WindowSize
		{
			return{ m_pRW->GetWidth(), m_pRW->GetHeight() };
		}

		auto OakVRRenderUnit::GetRenderWindowWidth()const -> float
		{
			return static_cast<float>(m_pRW->GetWidth());
		}

		auto OakVRRenderUnit::GetRenderWindowHeight() const -> float
		{
			return static_cast<float>(m_pRW->GetHeight());
		}

		auto OakVRRenderUnit::GetRenderWindowPositionX()const->float
		{
			return static_cast<float>(m_pRW->GetPositionX());
		}

		auto OakVRRenderUnit::GetRenderWindowPositionY()const ->float
		{
			return static_cast<float>(m_pRW->GetPositionY());
		}

		auto OakVRRenderUnit::SetRenderWindowTitle(const std::string &title) -> void
		{
			m_pRW->SetTitle(title);
		}

		auto OakVRRenderUnit::OnWindowSizeChanged(void *pNativeWindowHandle, int width, int height) -> void
		{
			if (m_pRW->GetNativeHandle() == reinterpret_cast<decltype(m_pRW->GetNativeHandle())>(pNativeWindowHandle))
			{
				m_pRW->SetSize(width, height);
				m_pRenderer->OnResize(m_pRW->GetWidth(), m_pRW->GetHeight());
				auto p = m_pCM->GetCurrentCamera();
				if (p)
					p->OnRenderWindowSizeChanged(static_cast<float>(width), static_cast<float>(height));
			}
		}

		auto OakVRRenderUnit::OnWindowFocusChanged(void *pNativeWindowHandle, int focused) -> void
		{
			if (m_pRW->GetNativeHandle() == reinterpret_cast<decltype(m_pRW->GetNativeHandle())>(pNativeWindowHandle))
			{
				m_pRW->OnFocusChanged(!!focused);

				// do other stuff related to fucus
			}
		}

		auto OakVRRenderUnit::OnWindowPositionChanged(void *pNativeWindowHandle, int x, int y) -> void
		{
			if (m_pRW->GetNativeHandle() == reinterpret_cast<decltype(m_pRW->GetNativeHandle())>(pNativeWindowHandle))
			{
				m_pRW->OnPositionChanged(x, y);
			}
		}


		bool OakVRRenderUnit::HasFocus()
		{
			return m_pRW->HasFocus();
		}

#define IMPLEMENT_DISABLEENABLE_FCT(paramName) \
	auto OakVRRenderUnit::Enable ## paramName () -> void\
			{\
		m_pRenderer->Enable ## paramName();\
			}\
	\
	auto OakVRRenderUnit::Disable ## paramName () -> void\
				{\
		m_pRenderer->Disable ## paramName();\
				}\
	\
	auto OakVRRenderUnit::Toggle ## paramName () -> void\
				{\
		m_pRenderer->Toggle ## paramName();\
				}\
	\
	bool OakVRRenderUnit::Is ## paramName ## Enabled() const\
			{\
		return m_pRenderer->Is ## paramName ## Enabled();\
			}

		IMPLEMENT_DISABLEENABLE_FCT(Wireframe)
		IMPLEMENT_DISABLEENABLE_FCT(Culling)
		IMPLEMENT_DISABLEENABLE_FCT(DepthTest)
		IMPLEMENT_DISABLEENABLE_FCT(Blending)
}