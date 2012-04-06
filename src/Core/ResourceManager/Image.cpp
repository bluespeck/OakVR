#include "Image.h"
#include "Core/ResourceManager/RawImageData.h"
#include "Core/ResourceManager/BMPLoader.h"
#include "Core/FileSystem/File.h"

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		Image::Image()
		{
		}

		// --------------------------------------------------------------------------------
		void Image::Init(const StringId &id, AdditionalInitParams *pInitParams)
		{
		}

		// --------------------------------------------------------------------------------
		void Image::Load()
		{
			Core::File file(m_id.GetStrId());
			Core::Buffer buff(file.Size());
			file.Read(buff.GetDataPtr(), buff.GetSize(), file.Size());
			m_pRawImageData = new RawImageData(BMPLoader::GetRawImage(buff));
		}

		// --------------------------------------------------------------------------------
		void Image::Reload()
		{
		}

		// --------------------------------------------------------------------------------
		void Image::Release()
		{
			delete m_pRawImageData;
		}
	}
}