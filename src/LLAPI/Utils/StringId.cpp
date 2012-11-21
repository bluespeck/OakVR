#include <cstring>

#include "StringId.h"

namespace ro3d
{
	std::map<uint32_t, std::set<std::string>> StringId::s_idsToStrings;

	uint32_t HashId(const uint8_t *data, int len);

#if defined(_DEBUG)
	// --------------------------------------------------------------------------------
	void StringId::TrackStrIdPair()
	{
			
		auto it = s_idsToStrings.find(m_id.first);
		if(it == s_idsToStrings.end())
		{
			std::set<std::string> strSet;
			strSet.insert(m_id.second);
			it->second = strSet;
		}
		else
		{
			it->second.insert(m_id.second);
		}
	}
#endif
	// --------------------------------------------------------------------------------
	StringId::StringId(uint32_t id)
	{
		m_id = std::make_pair(id, "id_to_string_" + std::to_string(id));
#if defined(_DEBUG)
	TrackStrIdPair();
#endif
	}

	// --------------------------------------------------------------------------------
	StringId::StringId(const std::string &strId)
	{
		m_id = std::make_pair(HashId(reinterpret_cast<const uint8_t *>(strId.c_str()), static_cast<int>(strId.size())), strId);	 
#if defined(_DEBUG)
		TrackStrIdPair();
#endif
	}
		
	// --------------------------------------------------------------------------------
	StringId::StringId(const char *strId)
	{
		m_id = std::make_pair(HashId(reinterpret_cast<const uint8_t *>(strId), static_cast<int>(strlen(strId))), strId);
#if defined(_DEBUG)
		TrackStrIdPair();
#endif
	}

	// --------------------------------------------------------------------------------
	void StringId::SetId(uint32_t id)
	{
		m_id = std::make_pair(id, "id_to_string_" + std::to_string(id));
#if defined(_DEBUG)
		TrackStrIdPair();
#endif
	}

	// --------------------------------------------------------------------------------
	void StringId::SetId(const std::string &strId)
	{
		m_id = std::make_pair(HashId(reinterpret_cast<const uint8_t *>(strId.c_str()), static_cast<int>(strId.size())), strId);	 
#if defined(_DEBUG)
		TrackStrIdPair();
#endif
	}
		
	// --------------------------------------------------------------------------------
	void StringId::SetId(const char *strId)
	{
		m_id = std::make_pair(HashId(reinterpret_cast<const uint8_t *>(strId), static_cast<int>(strlen(strId))), strId);
#if defined(_DEBUG)
		TrackStrIdPair();
#endif
	}

	// --------------------------------------------------------------------------------
	bool StringId::operator ==(const StringId &id) const
	{
		return m_id.first == id.m_id.first && m_id.second == id.m_id.second;
	}

	// --------------------------------------------------------------------------------
	bool StringId::operator <(const StringId &id) const
	{
		return m_id.first < id.m_id.first || m_id.second.compare(id.m_id.second) < 0;
	}

	// --------------------------------------------------------------------------------
	// Hash function code was taken from http://www.azillionmonkeys.com/qed/hash.html
	uint32_t HashId(const uint8_t *data, int len)
	{
		uint32_t hash = len, tmp;
		int rem;

		if (len <= 0 || data == NULL) return 0;

		rem = len & 3;
		len >>= 2;
			
#		define get16bits(d) (*((const uint16_t *) (d)))

		/* Main loop */
		for (;len > 0; len--) {
			hash  += get16bits (data);
			tmp    = (get16bits (data+2) << 11) ^ hash;
			hash   = (hash << 16) ^ tmp;
			data  += 2*sizeof (uint16_t);
			hash  += hash >> 11;
		}

		/* Handle end cases */
		switch (rem) {
		case 3:
			hash += get16bits (data);
			hash ^= hash << 16;
			hash ^= data[sizeof (uint16_t)] << 18;
			hash += hash >> 11;
			break;
		case 2:
			hash += get16bits (data);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1:
			hash += *data;
			hash ^= hash << 10;
			hash += hash >> 1;
		}

		/* Force "avalanching" of final 127 bits */
		hash ^= hash << 3;
		hash += hash >> 5;
		hash ^= hash << 4;
		hash += hash >> 17;
		hash ^= hash << 25;
		hash += hash >> 6;

		return hash;

#		undef get16bits
	}


}	// namespace ro3d
