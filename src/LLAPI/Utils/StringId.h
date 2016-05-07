#pragma once

#include <string>

namespace oakvr
{
	class StringId
	{
	public:
		inline StringId(const std::string & str);
		inline StringId(const char * str = "unknown");
		
		inline StringId(const StringId & other);
		inline StringId(StringId && other);

		inline char const * c_str() const;
		inline operator std::string ();
		inline operator const std::string() const;
		inline operator const char *() const;
		inline auto operator = (const StringId & other) -> StringId &;
		inline auto operator = (StringId && other) -> StringId &;

		inline auto operator == (const StringId & other) const -> bool;
		inline auto operator == (const std::string & other) const -> bool;
		inline auto operator == (const char * other) const -> bool;
		inline auto operator < (const StringId & other) const -> bool;

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

	inline char const * StringId::c_str() const
	{
		return m_id.c_str();
	}

	// --------------------------------------------------------------------------------
	inline auto StringId::operator = (const StringId & other) -> StringId &
	{
		m_id = other.m_id;
		return *this;
	}

	// --------------------------------------------------------------------------------
	inline auto StringId::operator = (StringId && other) -> StringId &
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
	inline auto StringId::operator == (const StringId & other) const -> bool
	{
		return m_id == other.m_id;
	}

	inline auto StringId::operator == (const std::string & other) const -> bool
	{
		return m_id == other;
	}

	inline auto StringId::operator == (const char *other) const -> bool
	{
		return m_id == other;
	}

	// --------------------------------------------------------------------------------
	inline auto StringId::operator < (const StringId & other) const -> bool
	{
		return m_id.compare(other.m_id) < 0;
	}
}	// namespace oakvr

template<>
struct std::hash < oakvr::StringId >
{
	auto operator()(const oakvr::StringId& _Keyval) const -> size_t
	{
		return std::hash < std::string > {} (_Keyval);
	}
};