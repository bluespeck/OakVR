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
			virtual auto Init() -> void;
			virtual auto Load() -> void;
			virtual auto Reload() -> void;
			virtual auto Release() -> void;
		};
	}
}

