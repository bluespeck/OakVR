
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_TEXTURE_H__
#define __OAK3D_INCLUDE_TEXTURE_H__

#include "Core/ResourceManager/IResource.h"
#include <cstdint>

namespace Oak3D
{
	namespace Render
	{

		class Texture :	public Oak3D::Core::IResource
		{
		public:
			enum TextureFormat
			{
				eTF_UNKNOWN = 0,
				eTF_A8R8G8B8_UNORM,
				eTF_X8R8G8B8_UNORM,
				eTF_A8R8G8B8_UINT,
				eTF_X8R8G8B8_UINT
			};

			// ctors & dtors
			Texture(void);
			~Texture(void);

			// accessors
			inline void *GetData();
			inline void SetData( void *pData );
		
			inline uint32_t GetWidth();			
			inline void SetWidth( uint32_t width );

			inline uint32_t GetHeight();
			inline void SetHeight( uint32_t height );

			inline uint32_t GetPitch();
			inline void SetPitch( uint32_t pitch );

			inline TextureFormat GetFormat();
			inline void SetFormat( TextureFormat textureFormat );

			// overrides
			void Init(const Oak3D::Core::StringId &id);
			void Load();
			void Reload();
			void Release();

		private:
			void *m_pData;

			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_pitch;
			TextureFormat m_textureFormat;
		};

		// --------------------------------------------------------------------------------		
		inline void *Texture::GetData()
		{
			return m_pData;
		}

		// --------------------------------------------------------------------------------
		inline void Texture::SetData( void *pData )
		{
			m_pData = pData;
		}

		// --------------------------------------------------------------------------------		
		inline uint32_t Texture::GetWidth()
		{
			return m_width;
		}
		
		// --------------------------------------------------------------------------------
		inline void Texture::SetWidth(uint32_t width)
		{
			m_width = width;
		}

		// --------------------------------------------------------------------------------		
		inline uint32_t Texture::GetHeight()
		{
			return m_height;
		}
		
		// --------------------------------------------------------------------------------
		inline void Texture::SetHeight(uint32_t height)
		{
			m_height = height;
		}

		// --------------------------------------------------------------------------------		
		inline uint32_t Texture::GetPitch()
		{
			return m_pitch;
		}

		// --------------------------------------------------------------------------------
		inline void Texture::SetPitch(uint32_t pitch)
		{
			m_pitch = pitch;
		}

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

	} // namespace Render
}	// namespace Oak3D

#endif
