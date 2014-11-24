#pragma once

#include "Utils/Buffer.h"

#include <cstdint>

namespace oakvr
{
	namespace render
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
			Texture(const oakvr::core::MemoryBuffer &buff);
			~Texture();
		
			void Use();

			TextureFormat GetFormat() const { return m_textureFormat; }

			void InvalidateContext() { m_contextIsValid = false; }

		private:
			class TextureImpl;
			std::unique_ptr<TextureImpl> m_pImpl;

			uint32_t m_width;
			uint32_t m_height;
			TextureFormat m_textureFormat;
			bool m_contextIsValid = true;
		};

	} // namespace render
}	// namespace oakvr
