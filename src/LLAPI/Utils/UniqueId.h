#pragma once

#include <cstdint>

namespace oakvr::core
{
	class UniqueId
	{
	public:
		UniqueId(): m_id(s_currentId++) {}
		auto Get() -> uint32_t { return m_id; }
	private:
		static uint32_t s_currentId;
		uint32_t m_id;
	};
}

