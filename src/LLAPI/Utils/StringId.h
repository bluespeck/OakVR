#pragma once

#include <string>

namespace oakvr
{
	class StringId
	{
	public:
		inline StringId(const std::string & str);
		inline StringId(const char * str);
		
		inline StringId(const StringId & other);
		inline StringId(StringId && other);

		inline operator std::string ();
		inline operator const std::string() const;
		inline operator const char *() const;
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

	inline StringId::StringId(const char * str)
	{
		m_id = std::string(str);
	}

	// --------------------------------------------------------------------------------
	inline StringId::StringId(const StringId & other)
	{
		m_id = other.m_id;
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
	inline StringId::operator const std::string() const
	{
		return m_id;
	}

	inline StringId::operator const char *() const
	{
		return m_id.c_str();
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

template<>
struct std::hash < oakvr::StringId >
{
	size_t operator()(const oakvr::StringId& _Keyval) const
	{
		return std::hash<std::string>()(_Keyval);
	}
};