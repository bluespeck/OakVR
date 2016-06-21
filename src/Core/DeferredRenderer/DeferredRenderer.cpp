#include "DeferredRenderer.h"
#include "DeferredRendererUtils.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Log/Log.h"

namespace oakvr
{
	namespace render
	{
		void DeferredRenderer::BeginObjectRender() noexcept
		{
			RenderCall renderCall{ RenderCallType::beginObjectRender };

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::EndObjectRender() noexcept
		{
			RenderCall renderCall{ RenderCallType::endObjectRender };

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::SetTexture(const oakvr::StringId &textureId) noexcept
		{
			RenderCall renderCall{ RenderCallType::setTexture };
			renderCall.textureId = textureId;

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::AddVertices(const oakvr::core::MemoryBuffer &vertices, VertexFormat vertexFormat) noexcept
		{
			RenderCall renderCall{ RenderCallType::addVertices };
			renderCall.vertexFormat = vertexFormat;
			renderCall.vertices = new oakvr::core::MemoryBuffer(vertices.Size());	// TODO: swap this new with an allocator based one
			memcpy(renderCall.vertices->GetDataPtr(), vertices.GetDataPtr(), vertices.Size());

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::SetVertexShader(const oakvr::StringId& vertexShaderId) noexcept
		{
			RenderCall renderCall{ RenderCallType::setVertexShader };
			renderCall.vsId = vertexShaderId;

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::SetPixelShader(const oakvr::StringId& pixelShaderId) noexcept
		{
			RenderCall renderCall{ RenderCallType::setPixelShader };
			renderCall.psId = pixelShaderId;

			AddRenderCall(renderCall);
		}

		void DeferredRenderer::AddRenderCall(const RenderCall& renderCall) noexcept
		{
			m_renderCallArray[m_updateBufferIndex][m_numRenderCalls[m_updateBufferIndex]++] = renderCall;
		}

		void DeferredRenderer::SwapRenderCallQueues() noexcept
		{
			std::swap(m_renderBufferIndex, m_updateBufferIndex);
		}

		void DeferredRenderer::RenderQueuedRenderCalls() noexcept
		{
			for (uint32_t i = 0; i < m_numRenderCalls[m_renderBufferIndex]; ++i )
			{
				auto& renderCall = m_renderCallArray[m_renderBufferIndex][i];
				switch (renderCall.type)
				{
				case RenderCallType::addVertices:
					AccumulateVertices(renderCall.vertices->GetDataPtr(), renderCall.vertexFormat, static_cast<uint32_t>(renderCall.vertices->Size()));
					break;
				case RenderCallType::beginObjectRender:
					break;
				case RenderCallType::endObjectRender:
					break;
				case RenderCallType::setColor:
					break;
				case RenderCallType::setPixelShader:
					UseShaderProgram(renderCall.psId);
					break;
				case RenderCallType::setTexture:
					AccumulateTextures(renderCall.textureId);
					break;
				case RenderCallType::setVertexShader:
					UseShaderProgram(renderCall.vsId);
					break;
				default:
					Log::Error("Unknown render call type!");
				}
			}
		}

		void DeferredRenderer::Flush() noexcept
		{
			oakvr::render::VertexBuffer vb{ m_rendererState.transformedVerticesIndex, GetVertexFormatStride(m_rendererState.vertexFormat) };
			void *destVertices;
			vb.Lock(&destVertices);
			memcpy(destVertices, m_rendererState.transformedVertices.data(), m_rendererState.transformedVerticesIndex);
			vb.Unlock();

			switch (m_rendererState.vertexFormat)
			{
			case oakvr::VertexFormat::xyz:
				vb.Use(std::vector<oakvr::render::VertexElementDescriptor> {
					oakvr::render::VertexElementDescriptor::Semantic::position});
				break;
			case oakvr::VertexFormat::xyz_nxyz:
				vb.Use(std::vector<oakvr::render::VertexElementDescriptor> {
					oakvr::render::VertexElementDescriptor::Semantic::position,
						oakvr::render::VertexElementDescriptor::Semantic::normal});
				break;
			case oakvr::VertexFormat::xyz_nxyz_uv:
				vb.Use(std::vector<oakvr::render::VertexElementDescriptor> {
					oakvr::render::VertexElementDescriptor::Semantic::position,
						oakvr::render::VertexElementDescriptor::Semantic::normal,
						oakvr::render::VertexElementDescriptor::Semantic::tex_coord});
				break;
			case oakvr::VertexFormat::xyz_uv:
				vb.Use(std::vector<oakvr::render::VertexElementDescriptor> {
					oakvr::render::VertexElementDescriptor::Semantic::position,
						oakvr::render::VertexElementDescriptor::Semantic::tex_coord});
				break;
			}
			DrawPrimitives(m_rendererState.transformedVerticesIndex / GetVertexFormatStride(m_rendererState.vertexFormat));
			m_rendererState.transformedVerticesIndex = 0;
		}

		void DeferredRenderer::AccumulateVertices(const void* vertices, oakvr::VertexFormat vertexFormat, uint32_t vertexCount) noexcept
		{
			if (vertexFormat != m_rendererState.vertexFormat)
			{
				Flush();
			}
			
			m_rendererState.vertexFormat = vertexFormat;

			uint8_t vertexStride = static_cast<uint8_t>(vertexFormat);
			auto pSource = reinterpret_cast<const uint8_t*>(vertices); 
			
			auto verticesToProcess = vertexCount;
			
			if (vertexStride * vertexCount + m_rendererState.transformedVerticesIndex > s_vertexBufferSize)
			{
				verticesToProcess = (s_vertexBufferSize - m_rendererState.transformedVerticesIndex) / vertexStride;
			}

			for (uint32_t i = 0; i < verticesToProcess; ++i)
			{
				auto *position = reinterpret_cast<const oakvr::math::Vector3 *>(pSource);
				auto *normal = reinterpret_cast<const oakvr::math::Vector3 *>(pSource + sizeof(oakvr::math::Vector3));
				
				auto transformedPosition = m_rendererState.worldMatrix * *position;
				auto transformedNormal = m_rendererState.worldMatrix * *normal;
				auto *pDestination = &m_rendererState.transformedVertices[m_rendererState.transformedVerticesIndex];
				memcpy(pDestination, &transformedPosition, sizeof(transformedPosition));
				memcpy(pDestination, &transformedNormal, sizeof(transformedNormal));
				memcpy(pDestination, pSource + 2 * sizeof(oakvr::math::Vector3), vertexStride - 2 * sizeof(oakvr::math::Vector3));
				m_rendererState.transformedVerticesIndex += vertexStride;
			}

			if (verticesToProcess < vertexCount)
			{
				Flush();
				AccumulateVertices(pSource + vertexStride * verticesToProcess, vertexFormat, vertexCount - verticesToProcess);
			}
		}
	}	// namespace render
} // namespace oakvr