#pragma once

#include <cstdint>

namespace oakvr
{
	namespace core
	{
		class UniqueId
		{
		public:
			UniqueId(): m_id(s_currentId++) {}
			uint32_t Get() { return m_id; }
		private:
			static uint32_t s_currentId;
			uint32_t m_id;
		};
	}
}

