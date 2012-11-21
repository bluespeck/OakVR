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
			Image(const StringId &id);
						
		private:
			RawImageData *m_pRawImageData;
		protected:
			virtual void Init();
			virtual void Load();
			virtual void Reload();
			virtual void Release();
		};
	}
}

