#pragma once

#include "Utils/Types.h"

#include <memory>

namespace oakvr
{
	template <typename T>
	class Octree
	{
	public:
		void Add(sp<T> m_pNod)
	private:
		struct Node
		{
			sp<T> m_pNodeData;
		};
	};
}