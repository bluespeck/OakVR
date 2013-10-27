#pragma once

#include <memory>
#include <cstdlib>

namespace oakvr
{
	template <typename T>
	class Buffer
	{
		Buffer();
		Buffer(std::size_t size);
		Buffer(const Buffer & buffer);
		Buffer(Buffer && buffer);
		Buffer & operator=(const Buffer & buffer);
		Buffer & operator=(Buffer && buffer);
		~Buffer();

		size_t Size() { return m_size; }

	private:
		T * m_buffer = nullptr;
		size_t m_size = 0;
	};

	//------------------------------------------------------
	template <typename T>
	Buffer<T>::Buffer()
	{
	}

	//------------------------------------------------------
	template <typename T>
	Buffer<T>::Buffer(std::size_t size)
	{
		m_buffer = new T[size];
		m_size = size;
	}

	//------------------------------------------------------
	template <typename T>
	Buffer<T>::Buffer(const Buffer & buffer)
	{
		m_size = buffer.Size();
		m_buffer = new T[m_size];
		memcpy(m_buffer, buffer.m_buffer, m_size);
	}

	//------------------------------------------------------
	template <typename T>
	Buffer<T>::Buffer(Buffer && buffer)
	{
		m_size = buffer.m_size;
		m_buffer = buffer.m_buffer;
		buffer.m_buffer = nullptr;
		buffer.m_size = 0;
	}

	//------------------------------------------------------
	template <typename T>
	Buffer & Buffer<T>::operator=(const Buffer & buffer)
	{
		m_size = buffer.size;
		m_buffer = new T[m_size];
		memcpy(m_buffer, buffer.m_buffer, m_size);
		return *this;
	}

	//------------------------------------------------------
	template <typename T>
	Buffer & Buffer<T>::operator=(Buffer && buffer)
	{
		m_size = std::move(buffer.m_size);
		m_buffer = std::move(buffer.m_buffer);
		return *this;
	}

	//------------------------------------------------------
	template <typename T>
	Buffer<T>::~Buffer()
	{
		delete m_buffer;
	}
}
