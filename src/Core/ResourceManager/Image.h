#pragma once

#include <cstdint>
#include "IResource.h"

namespace ro3d
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

