#include "Common.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Renderer.h"
#include "Utils/RenderUtils.h"
#include "Log/Log.h"
#include "Utils/BufferReader.h"

#include <string>
#include <cassert>
#include <memory>

namespace oakvr::render
{
	class Texture::TextureImpl
	{
	public:
		GLuint textureId;
	};

	Texture::Texture(const oakvr::core::MemoryBuffer& buff)
		: m_pImpl{ std::make_unique<TextureImpl>() }
	{
		glCallAndCheck(glGenTextures, 1, &m_pImpl->textureId);
		glCallAndCheck(glBindTexture, GL_TEXTURE_2D, m_pImpl->textureId);

		uint32_t width, height;
		uint32_t bitsPerPixel;
		TextureFormat textureFormat;
		auto reader = oakvr::core::MakeBufferReader(buff);
		reader.Read(width);
		reader.Read(height);
		reader.Read(bitsPerPixel);
		reader.Read(textureFormat);
		oakvr::core::MemoryBuffer pixelData(width * height * bitsPerPixel / 8);
		reader.Read(pixelData.GetDataPtr(), pixelData.Size());

		GLint format = GL_RGBA;
		GLuint internalFormat = GL_RGBA;
		switch (textureFormat)
		{
		case TextureFormat::argb:
			format = GL_RGBA;
			break;
		case TextureFormat::bgra:
			format = GL_BGRA;
			break;
		case TextureFormat::rgb:
			format = GL_RGB;
			break;
		case TextureFormat::alpha:
			format = GL_RED;
			internalFormat = GL_RED;
			break;
		default:
			format = GL_RGBA;
			break;
		}
		glCallAndCheck(glTexImage2D, GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixelData.GetDataPtr());

		glCallAndCheck(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glCallAndCheck(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	Texture::~Texture()
	{
		if (m_contextIsValid)
			glCallAndCheck(glDeleteTextures, 1, &m_pImpl->textureId);
	}

	auto Texture::GetNativeHandle() const noexcept -> void*
	{
		return reinterpret_cast<void*>(m_pImpl->textureId);
	}
}