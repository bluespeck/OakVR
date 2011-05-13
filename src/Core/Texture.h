
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_TEXTURE_H__
#define __OAK3D_INCLUDE_TEXTURE_H__

#include "IResource.h"
#include <cstdint>

namespace Oak3D
{
	namespace Core
	{

		class Texture :	public IResource
		{
		public:
			enum TextureFormat
			{
				eTF_UNKNOWN = 0,
				eTF_R8G8B8A8_UNORM,
				eTF_R8G8B8X8_UNORM,
				eTF_R8G8B8A8_UINT
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

			inline TextureFormat GetFormat();
			inline void SetFormat( TextureFormat textureFormat );

			// overrides
			void Init(const std::wstring &path);
			void Load();
			void Reload();
			void Release();

		private:
			void *m_pData;

			uint32_t m_width;
			uint32_t m_height;
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
		inline Texture::TextureFormat Texture::GetFormat()
		{
			return m_textureFormat;
		}

		// --------------------------------------------------------------------------------
		inline void Texture::SetFormat( Texture::TextureFormat textureFormat )
		{
			m_textureFormat = textureFormat;
		}

	} // namespace Core
}	// namespace Oak3D

#endif
