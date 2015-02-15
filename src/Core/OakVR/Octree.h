#pragma once

#include "Utils/Types.h"

#include <memory>
#include <array>

namespace oakvr
{
	template <typename T>
	class Octree
	{
	public:
		auto Add(sp<T> m_pData) -> void;
	private:
		struct Node
		{
			sp<T> m_pNodeData;
			std::array < sp<Node>, 8 > m_children;
		};
	};
}