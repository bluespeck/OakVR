#ifndef __OAK3D_INCLUDE_IRESOURCE_H__
#define __OAK3D_INCLUDE_IRESOURCE_H__

#include <string>
#include "../Utils/StringID.h"

namespace Oak3D
{
	namespace Core
	{

		class IResource
		{
		public:
			IResource() : m_id(0) {}
			virtual ~IResource() {}
	
			virtual void Init(const std::wstring &path) = 0;
			virtual void Load() = 0;
			virtual void Reload() = 0;
			virtual void Release() = 0;

		protected:
			Utils::StringID m_id;
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
