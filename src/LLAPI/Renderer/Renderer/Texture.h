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
			};

			// ctors & dtors
			Texture(const oakvr::core::MemoryBuffer &buff);
			~Texture();
		
			void Use();

			inline TextureFormat GetFormat();
			inline void SetFormat( TextureFormat textureFormat );
			

		private:
			class TextureImpl;
			std::unique_ptr<TextureImpl> m_pImpl;

			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_pitch;
			TextureFormat m_textureFormat;
		};

		// --------------------------------------------------------------------------------
		inline Texture::TextureFormat Texture::GetFormat()
		{
			return m_textureFormat;
		}

		// --------------------------------------------------------------------------------
		inline void Texture::SetFormat( Texture::TextureFormat textureFormat )
		{
			m_textureFormat = textureFormat;
		}

	} // namespace render
}	// namespace oakvr
