#pragma once

#include <string>
#include <cstdint>
#include <map>
#include <set>

namespace oakvr
{
	class StringId
	{
	public:
		typedef std::pair<std::uint32_t, std::string> StrIdPair;

		StringId(uint32_t id);
		StringId(const std::string &strId);
		StringId(const char *strId);
		
		void SetId(uint32_t id);
		void SetId(const std::string &strId);
		void SetId(const char *strId);

		const StrIdPair &GetId() const { return m_id; }

		bool operator ==(const StringId &id) const ;
		bool operator <(const StringId &id) const;

		

	private:
		StrIdPair m_id;
				
#if defined (_DEBUG)				
		void TrackStrIdPair();
		static std::map<uint32_t, std::set<std::string>> s_idsToStrings; // for duplicates checking
#endif
	};
}	// namespace oakvr
