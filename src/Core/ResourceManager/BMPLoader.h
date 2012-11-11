#ifndef __OAK3D_INCLUDE_CORE_BMPLOADER_H__
#define __OAK3D_INCLUDE_CORE_BMPLOADER_H__

#include <cstdint>
#include <string>

#include "RawImageData.h"

namespace ro3d
{
	namespace Core
	{
		class BMPLoader
		{
		public:
			static RawImageData GetRawImage(Buffer &fileBuffer);
		};
	}
}

#endif
