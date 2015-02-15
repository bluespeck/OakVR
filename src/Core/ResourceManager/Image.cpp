#include "Image.h"
#include "ResourceManager/RawImageData.h"
#include "ResourceManager/BMPLoader.h"
#include "FileIO/File.h"

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		Image::Image(const StringId &id)
			:IResource(id)
		{
		}

		// --------------------------------------------------------------------------------
		auto Image::Init() -> void
		{
		}

		// --------------------------------------------------------------------------------
		auto Image::Load() -> void
		{
			core::io::File file(m_id);
			core::MemoryBuffer buff(file.Size());
			file.Read(buff.GetDataPtr(), buff.Size(), file.Size());
			//m_pRawImageData = new RawImageData(BMPLoader::GetRawImage(buff));
		}

		// --------------------------------------------------------------------------------
		auto Image::Reload() -> void
		{
		}

		// --------------------------------------------------------------------------------
		auto Image::Release() -> void
		{
			delete m_pRawImageData;
		}
	}
}
