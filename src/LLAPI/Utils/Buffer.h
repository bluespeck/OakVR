#pragma once

#include <memory>
#include <cstdlib>

namespace oakvr
{
	namespace core
	{
		template <typename T>
		class Buffer
		{
		public:
			typedef T value_type;
			Buffer() = default;
			Buffer(std::size_t size);
			Buffer(const Buffer & buffer);
			Buffer(Buffer && buffer);
			auto operator = (const Buffer & buffer) -> Buffer &;
			auto operator = (Buffer && buffer) -> Buffer &;
			~Buffer();

			auto Size() const -> size_t {
				return m_size; }
			auto Resize(std::size_t size) -> void;

			auto GetDataPtr() const -> value_type const * { 
				return m_buffer; }
			auto GetDataPtr() -> value_type *{ 
				return m_buffer; }

		private:
			value_type * m_buffer = nullptr;
			size_t m_size = 0;
		};

		typedef Buffer<uint8_t> MemoryBuffer;

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
		auto Buffer<T>::operator=(const Buffer<T> & buffer) -> Buffer<T> &
		{
			m_size = buffer.m_size;
			m_buffer = new T[m_size];
			memcpy(m_buffer, buffer.m_buffer, m_size);
			return *this;
		}

		//------------------------------------------------------
		template <typename T>
		auto Buffer<T>::operator=(Buffer<T> && buffer) -> Buffer<T> &
		{
			m_size = std::move(buffer.m_size);
			m_buffer = std::move(buffer.m_buffer);
			buffer.m_size = 0;
			buffer.m_buffer = nullptr;
			return *this;
		}
		//------------------------------------------------------
		template <typename T>
		auto Buffer<T>::Resize(std::size_t size) -> void
		{
			auto pNewBuffer = new T[size];
			if (m_size)
			{
				memcpy(pNewBuffer, m_buffer, m_size);
				delete[] m_buffer;
			}
			m_buffer = pNewBuffer;
			m_size = size;
		}

		//------------------------------------------------------
		template <typename T>
		Buffer<T>::~Buffer()
		{
			if (m_size)
				delete m_buffer;
		}
	}	// namespace core
}	// namespace oakvr
