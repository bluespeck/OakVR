#include "Common.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Renderer.h"
#include "Utils/RendererUtils.h"
#include "Log/Log.h"
#include "Utils/BufferReader.h"

#include <string>
#include <cassert>
#include <memory>

namespace oakvr
{
	namespace render
	{
		class Texture::TextureImpl
		{
		public:
			GLuint textureId;
		};

		Texture::Texture(const oakvr::core::MemoryBuffer &buff)
			: m_pImpl {std::make_unique<TextureImpl>()}
		{
			glGenTextures(1, &m_pImpl->textureId);

			glBindTexture(GL_TEXTURE_2D, m_pImpl->textureId);
#ifdef OAKVR_RENDER_DEBUG
			{
				GLenum err = glGetError();
				if (err)
					Log::PrintWarning("1OpenGL texture creation has failed : 0x%x", err);
			}
#endif
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
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixelData.GetDataPtr());

#ifdef OAKVR_RENDER_DEBUG
			{
				GLenum err = glGetError();
				if(err)
					Log::PrintWarning("2OpenGL texture creation has failed : 0x%x", err);
			}
#endif

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}
			
		Texture::~Texture()
		{
			glDeleteTextures(1, &m_pImpl->textureId);
		}

		void Texture::Use()
		{
			glBindTexture(GL_TEXTURE_2D, m_pImpl->textureId);
		}
	}
}