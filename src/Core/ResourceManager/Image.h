#pragma once

#include <cstdint>
#include "IResource.h"

namespace oakvr
{
	namespace core
	{
		struct RawImageData;
		class Image : public IResource
		{
		public:
			Image(const StringId &id);
						
		private:
			RawImageData *m_pRawImageData = nullptr;
		protected:
			virtual void Init();
			virtual void Load();
			virtual void Reload();
			virtual void Release();
		};
	}
}

