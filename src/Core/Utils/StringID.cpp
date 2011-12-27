#include "StringID.h"
#include <functional>

namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		StringId::StringId(uint32_t id)
		{
			m_id = id;
			m_strId = std::to_string((long long)m_id);
		}

		// --------------------------------------------------------------------------------
		StringId::StringId(const std::string &strId)
		:m_strId(strId)
		{			
			std::hash<std::string> h;
			m_id = h(strId);
		}
		
		StringId::StringId(const char *strId)
		{
			m_strId = strId;
			std::hash<std::string> h;
			m_id = h(m_strId);
		}

		// --------------------------------------------------------------------------------
		void StringId::SetStrId(const std::string &strId)
		{
			m_strId = strId;
			std::hash<std::string> h;
			m_id = h(m_strId);
		}

	}	// namespace Core
}	// namespace Oak3D
