#pragma once

#include <memory>
#include <cstdint>

namespace oakvr::render
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(uint32_t count, uint8_t stride);
		~IndexBuffer();

		auto GetIndexCount() const -> uint32_t {
			return m_count;
		}
		auto GetIndexStride() const -> uint8_t {
			return m_stride;
		}

		auto Create(uint32_t count, uint8_t stride) -> void;
		auto Lock(void** ppBuff, uint32_t offsetToLock = 0, uint32_t sizeToLock = 0, uint32_t flags = 0) -> void;
		auto Unlock() -> void;
		auto Release() -> void;

		auto Use() -> void;
	private:
		class IndexBufferImpl;
		std::unique_ptr<IndexBufferImpl> m_pImpl;

		uint32_t m_count = 0;
		uint8_t m_stride = 0;

	};
}
