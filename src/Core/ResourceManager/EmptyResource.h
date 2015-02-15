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
		virtual auto Init()  -> void{};
		virtual auto Load()  -> void{};
		virtual auto Reload()  -> void{};
		virtual auto Release()  -> void{};
	};
} // end namespace oakvr
