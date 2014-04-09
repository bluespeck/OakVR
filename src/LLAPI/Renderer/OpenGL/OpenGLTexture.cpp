#include "Common.h"
#include "Renderer/Renderer/Texture.h"
#include "Renderer/Renderer/Renderer.h"
#include "Renderer/Renderer/RendererUtils.h"
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

			//			oakvr::core::Image *pImage = oakvr::Engine::GetResourceManager()->GetResource<oakvr::core::Image>(pTexture->GetId().GetStrId().c_str());
			// Separate resources on unique threads
			//			assert("Could not load texture from file!" && texId > 0);

			glBindTexture(GL_TEXTURE_2D, m_pImpl->textureId);
			uint32_t width, height;
			uint32_t bitsPerPixel;
			TextureFormat textureFormat;
			oakvr::core::BufferReader<oakvr::core::MemoryBuffer::value_type, uint32_t>reader(buff);
			reader.Read(width);
			reader.Read(height);
			reader.Read(bitsPerPixel);
			reader.Read(textureFormat);
			oakvr::core::MemoryBuffer pixelData(width * height * bitsPerPixel / 8);
			reader.Read(pixelData.GetDataPtr(), pixelData.Size());
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData.GetDataPtr());
#ifdef OAKVR_RENDER_DEBUG
			GLenum err = glGetError();
			if(err)
				Log::PrintWarning("OpenGL texture creation has failed : 0x%x", err);
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