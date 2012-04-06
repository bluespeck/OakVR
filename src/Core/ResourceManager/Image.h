#ifndef __OAK3D_INCLUDE_CORE_IMAGE_H__
#define __OAK3D_INCLUDE_CORE_IMAGE_H__

#include <cstdint>
#include "IResource.h"

namespace Oak3D
{
	namespace Core
	{
		struct RawImageData;
		class Image : public IResource
		{
		public:
			Image();

			virtual void Init(const StringId &id, AdditionalInitParams *pInitParams);
			virtual void Load();
			virtual void Reload();
			virtual void Release();
		private:
			RawImageData *m_pRawImageData;
		};
	}
}

#endif
