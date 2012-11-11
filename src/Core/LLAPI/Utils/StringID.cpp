#include "StringId.h"

namespace Oak3D
{
	namespace Core
	{
		uint32_t HashId(const uint8_t *data, int len);
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
			m_id = HashId((const uint8_t *)strId.c_str(), strId.size());
		}
		
		StringId::StringId(const char *strId)
		{
			m_strId = strId;
			m_id = HashId((const uint8_t *)strId, strlen(strId));
		}

		// --------------------------------------------------------------------------------
		void StringId::SetStrId(const std::string &strId)
		{
			m_strId = strId;
			m_id = HashId((const uint8_t *)strId.c_str(), strId.size());
		}

		// --------------------------------------------------------------------------------
		bool StringId::operator ==(const StringId &id) const
		{
			return m_id == id.m_id;
		}

		// --------------------------------------------------------------------------------
		bool StringId::operator <(const StringId &id) const
		{
			return m_id < id.m_id;
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
			
#           define get16bits(d) (*((const uint16_t *) (d)))

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
				case 3: hash += get16bits (data);
						hash ^= hash << 16;
						hash ^= data[sizeof (uint16_t)] << 18;
						hash += hash >> 11;
						break;
				case 2: hash += get16bits (data);
						hash ^= hash << 11;
						hash += hash >> 17;
						break;
				case 1: hash += *data;
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
		}
#       undef get16bits

	}	// namespace Core
}	// namespace Oak3D
