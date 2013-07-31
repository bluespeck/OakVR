// this is a placeholder resource, used to keep track of
// a resource through the loading process; under normal
// circumstances, it shouldn't be used in user code

#pragma once

#include "ResourceManager/IResource.h"

namespace oakvr
{
	class EmptyResource : public IResource
	{
	public:
		EmptyResource(const oakvr::StringId &id): IResource(id) { m_type = "EmptyResource"; }
		~EmptyResource() {}
	protected:
		virtual void Init() {};
		virtual void Load() {};
		virtual void Reload() {};
		virtual void Release() {};
	};
} // end namespace ro3d
