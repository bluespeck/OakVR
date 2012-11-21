#include "Image.h"
#include "ResourceManager/RawImageData.h"
#include "ResourceManager/BMPLoader.h"
#include "FileIO/File.h"

namespace ro3d
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		Image::Image(const StringId &id)
			:IResource(id)
		{
		}

		// --------------------------------------------------------------------------------
		void Image::Init()
		{
		}

		// --------------------------------------------------------------------------------
		void Image::Load()
		{
			Core::File file(m_id.GetId().second);
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