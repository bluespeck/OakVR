#pragma once

#include "Utils/Types.h"
#include "Math/Vector3.h"

#include <memory>
#include <array>
#include <cstdint>

namespace oakvr
{

	// min size is 1
	template <typename T, uint32_t size = 4096>
	class Octree
	{
	public:
		auto Insert(const oakvr::math::Vector3 &pos, sp<T> pData) -> void;

		const uint32_t m_size = size;
	private:
		struct Node
		{
			oakvr::math::Vector3 m_position;
			sp<T> m_pNodeData;
			std::array < up<Node>, 8 > m_children;
		};
	};

	template<typename T, uint32_t size>
	auto Octree<T, size>::Insert(const oakvr::math::Vector3 &pos, sp<T> pData) -> void
	{
	}
}