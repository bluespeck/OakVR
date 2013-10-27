#pragma once

#include <string>

namespace oakvr
{
	class StringId
	{
	public:
		inline StringId(const std::string & str);
		
		inline StringId(const StringId & other);
		inline StringId(StringId && other);

		inline operator std::string ();
		inline StringId & operator = (const StringId & other);
		inline StringId & operator = (StringId && other);

		inline bool operator == (const StringId & other) const;
		inline bool operator < (const StringId & other) const;


		

	private:
		std::string m_id;
	};

	// --------------------------------------------------------------------------------
	inline StringId::StringId(const std::string & str)
	{
		m_id = str;
	}

	// --------------------------------------------------------------------------------
	inline StringId::StringId(StringId && other)
	{
		m_id = std::move(other.m_id);
	}

	// --------------------------------------------------------------------------------
	inline StringId & StringId::operator = (const StringId & other)
	{
		m_id = other.m_id;
		return *this;
	}

	// --------------------------------------------------------------------------------
	inline StringId & StringId::operator = (StringId && other)
	{
		m_id = std::move(other.m_id);
		return *this;
	}

	// --------------------------------------------------------------------------------
	inline StringId::operator std::string ()
	{
		return m_id;
	}

	// --------------------------------------------------------------------------------
	inline bool StringId::operator == (const StringId & other) const
	{
		return m_id == other.m_id;
	}

	// --------------------------------------------------------------------------------
	inline bool StringId::operator < (const StringId & other) const
	{
		return m_id.compare(other.m_id) < 0;
	}
}	// namespace oakvr
