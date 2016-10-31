#pragma once

#include "DeferredRendererUtils.h"
#include "Utils/Types.h"
#include "Utils/StringId.h"
#include "Utils/Buffer.h"
#include "Math/Matrix.h"
#include "Renderer/Renderer/Renderer.h"

#include <array>
#include <unordered_map>


namespace oakvr
{	
	namespace render
	{
		class Renderable;

		class DeferredRenderer : public Renderer
		{
		public:
			static constexpr uint32_t s_maxNumRenderCalls = 32768;
			static constexpr uint32_t s_vertexBufferSize = 32 * 1024 * 1024; // 32MB

		public:
			DeferredRenderer() = default;

			void BeginObjectRender() noexcept;
			void EndObjectRender() noexcept;
			void SetTexture(const oakvr::StringId &textureId) noexcept;
			void AddVertices(const oakvr::core::MemoryBuffer &vertices, VertexFormat vertexFormat) noexcept;
			void SetWorldMatrix(const oakvr::math::Matrix &worldMatrix) noexcept { m_rendererState.worldMatrix = worldMatrix; }
			void SetViewMatrix(const oakvr::math::Matrix &viewMatrix) noexcept { m_rendererState.viewMatrix = viewMatrix; }
			void SetProjectionMatrix(const oakvr::math::Matrix &projectionMatrix) noexcept { m_rendererState.projectionMatrix = projectionMatrix; }
			void SetVertexShader(const oakvr::StringId& vertexShaderId) noexcept;
			void SetPixelShader(const oakvr::StringId& pixelShaderId) noexcept;

			void RenderQueuedRenderCalls() noexcept;

			void Update(double dt) noexcept override;
			void Render() noexcept override;
			void SwapBuffers() noexcept override;

		private:
			void AddRenderCall(const RenderCall& renderCall) noexcept;

			void AccumulateVertices(const void* vertices, oakvr::VertexFormat vertexFormat, uint32_t vertexCount) noexcept;
			void AccumulateTexture(const oakvr::StringId& textureId) noexcept;
			void Flush() noexcept;

			void RenderRenderables(const std::vector<sp<Renderable>> &renderables) ;

			// swap when all update threads have finished running
			void SwapRenderCallQueues() noexcept;

			struct RendererState
			{
				oakvr::math::Matrix worldMatrix;
				oakvr::math::Matrix viewMatrix;
				oakvr::math::Matrix projectionMatrix;
				oakvr::PixelShader* pixelShader;
				oakvr::VertexShader* vertexShader;
				using VertexArray = std::array<uint8_t, s_vertexBufferSize>;
				VertexArray transformedVertices;
				uint32_t transformedVerticesIndex = 0;
				oakvr::VertexFormat vertexFormat;
			};


			using RenderCallArray = std::array<RenderCall, s_maxNumRenderCalls>;
			using BufferIndex = uint8_t;
			static constexpr BufferIndex s_numBuffers = 2;
			uint32_t m_numRenderCalls[s_numBuffers] = { 0 };
			RenderCallArray m_renderCallArray[s_numBuffers];
			BufferIndex m_updateBufferIndex = 0;
			BufferIndex m_renderBufferIndex = 1;

			RendererState m_rendererState;
		};
	} // namespace render
} // namespace oakvr
