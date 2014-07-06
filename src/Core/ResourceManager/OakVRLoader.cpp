#include "OakVRLoader.h"

namespace oakvr
{
	namespace core
	{
		// --------------------------------------------------------------------------------
		MemoryBuffer OakVRLoader::GetResourceData(const MemoryBuffer &fileBuffer)
		{
			const size_t signatureSize = 4;
			MemoryBuffer mb(fileBuffer.Size() - signatureSize);
			memcpy(mb.GetDataPtr(), fileBuffer.GetDataPtr() + signatureSize, mb.Size());
			return mb;
		}

		// --------------------------------------------------------------------------------
		bool OakVRLoader::CanLoad(const MemoryBuffer &fileBuffer)
		{
			auto p = fileBuffer.GetDataPtr();

			return fileBuffer.Size() > 4 && p[0] == 'O' && p[1] == 'K' && p[2] == 'V' && p[3] == 'R';
		}
	}
}