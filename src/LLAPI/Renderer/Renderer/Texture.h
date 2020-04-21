#pragma once

#include "Utils/Buffer.h"

#include <cstdint>

namespace oakvr::render
{

	class Texture
	{
	public:
		enum class TextureFormat
		{
			unknown,
			argb,
			rgb,
			bgra,
			alpha
		};

		// ctors & dtors
		Texture(const oakvr::core::MemoryBuffer& buff);
		~Texture();

		auto GetFormat() const noexcept -> TextureFormat { return m_textureFormat; }

		auto InvalidateContext() noexcept -> void { m_contextIsValid = false; }

		auto GetNativeHandle() const noexcept -> void*;

	private:
		class TextureImpl;
		std::unique_ptr<TextureImpl> m_pImpl;

		uint32_t m_width;
		uint32_t m_height;
		TextureFormat m_textureFormat;
		bool m_contextIsValid = true;
	};
}
