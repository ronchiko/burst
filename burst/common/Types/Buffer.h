#pragma once

#include "../Error.h"
#include "../Types.h"

namespace burst {

	/**
	 * A class that represents data, automatically infers if it should be owned
	 * or not.
	 * 
	 * \note: All implicit conversions are non owning
	 */
	template<typename T>
	class Buffer final
	{
	public:
		/**
		 * The buffer references data.
		 * 
		 * \note: The buffer is non owning
		 */
		constexpr explicit Buffer(T* data, u32 size)
			: m_Size(size)
			, m_Buffer(data)
			, m_IsOwner(false)
		{}

		Buffer(const Buffer& buffer)
			: m_Size(buffer.m_Size)
			, m_Buffer(buffer.m_Buffer)
			, m_IsOwner(false)
		{}

		Buffer(Buffer&& buffer)
			: m_Size(buffer.m_Size)
			, m_Buffer(buffer.m_Buffer)
			, m_IsOwner(buffer.m_IsOwner)
		{
			buffer._reset();
		}

		Buffer& operator=(const Buffer& buffer) {
			_release();

			m_Size = buffer.m_Size;
			m_Buffer = _create_and_copy(buffer.m_Buffer, buffer.m_Size);
			m_IsOwner = true;

			return *this;
		}

		Buffer& operator=(Buffer&& buffer)
		{
			_release();

			m_Size = buffer.m_Size;
			m_Buffer = buffer.m_Buffer;
			m_IsOwner = buffer.m_IsOwner;

			buffer._reset();

			return *this;
		}

		Buffer(const Span<char>& span)
			: m_Size(span.size())
			, m_Buffer(span.data())
			, m_IsOwner(false)
		{}

		// Implicit non owning constructor of a vector
		Buffer(const Vector<char>& buffer)
			: m_Size(static_cast<u32>(buffer.size()))
			, m_Buffer(const_cast<T *>(buffer.data()))
			, m_IsOwner(false)
		{}

		/**
		 * Clones a vector into a new buffer.
		 */
		static Buffer clone(const Vector<T>& vector);

		/**
		 * Clones a vector into a new buffer.
		 */
		static Buffer clone(const Buffer<T>& vector);

		/**
		 * Allocate a new buffer with a given size.
		 * 
		 * \param size: The amount of elements in the buffer
		 * 
		 * \note: The buffer owns the data
		 */
		static Buffer allocate(u32 size);

		/**
		 * Gets an item from the buffer at a given index.
		 */
		T& operator[](u32 index);

		/**
		 * Gets an item for the buffer a given index.
		 */
		const T& at(u32 index) const;

		/**
		 * The amount of items in the buffer.
		 */
		constexpr inline u32 size() const;

		/**
		 * Gets the data inside this buffer.
		 */
		constexpr inline T *data();

		/**
		 * Gets the data inside this buffer.
		 */
		constexpr const T *data() const;

		/**
		 * The size of the buffer in bytes.
		 */
		constexpr u32 size_in_bytes() const;

		/**
		 * Resizes this buffer.
		 *
		 * \param size: The new size of the buffer (in elements)
		 */
		void resize(u32 size);

		/**
		 * Either returns this buffer if it owns its data, or
		 * returns a copy of this one if this buffer doesn't
		 * own its data.
		 * 
		 * \note: Dont use on refernced buffers!
		 * 
		 * \note: After a call to this method, further usage of the buffer
		 *		  is undefined.
		 */
		inline Buffer ensure_ownership();

	private:
		explicit Buffer(u32 size, T* buffer, bool owner)
			: m_Size(size)
			, m_Buffer(buffer)
			, m_IsOwner(owner)
		{}

		// Releases the currently owned buffer
		void _release();

		// Resets the buffers data
		void _reset();

		// Creates an copies a buffer's buffer into another
		static T *_create_and_copy(const T *buffer, size_t size);

		u32 m_Size;
		T *m_Buffer;
		bool m_IsOwner;
	};
}

template<typename T>
burst::Buffer<T> burst::Buffer<T>::allocate(u32 size)
{
	return Buffer(size, new T[size], true);
}

template<typename T>
burst::Buffer<T> burst::Buffer<T>::clone(const Vector<T>& v)
{
	return Buffer(v.size(), _create_and_copy(v.data(), v.size()), true);
}

template<typename T>
burst::Buffer<T> burst::Buffer<T>::clone(const Buffer<T>& v)
{
	return Buffer(v.m_Size, _create_and_copy(v.m_Buffer, v.m_Size), true);
}

template<typename T>
void burst::Buffer<T>::_reset() {
	m_Buffer = nullptr;
	m_Size = 0;
	m_IsOwner = false;
}

template<typename T>
void burst::Buffer<T>::_release()
{
	if(nullptr == m_Buffer) {
		return;
	}
	
	if(m_IsOwner) {
		delete[] m_Buffer;
	}
	
	_reset();
}

template<typename T>
inline T *burst::Buffer<T>::_create_and_copy(const T *buffer, size_t size)
{
	T *new_buffer = new T[size];
	try {
		std::copy(buffer, buffer + size, new_buffer);

		return new_buffer;
	} catch(const std::exception&) {
		delete[] new_buffer;
		throw;
	}
}

template<typename T>
inline T& burst::Buffer<T>::operator[](u32 index)
{
	if(m_Size <= index) {
		throw std::out_of_range();
	}

	return m_Buffer[index];
}

template<typename T>
inline const T& burst::Buffer<T>::at(u32 index) const
{
	return const_cast<Buffer&>(*this)[index];
}

template<typename T>
constexpr inline burst::u32 burst::Buffer<T>::size() const
{
	return m_Size;
}

template<typename T>
constexpr inline T* burst::Buffer<T>::data()
{
	return m_Buffer;
}

template<typename T>
constexpr inline const T *burst::Buffer<T>::data() const
{
	return m_Buffer;
}

template<typename T>
constexpr inline burst::u32 burst::Buffer<T>::size_in_bytes() const
{
	return m_Size * sizeof(T);
}

template<typename T>
inline void burst::Buffer<T>::resize(u32 size)
{
	Unique<T[]> new_buffer = nullptr;
	try {
		new_buffer = new T[size];
		auto copy_size = std::min(size, m_Size);
		std::copy(m_Buffer, m_Buffer + copy_size, new_buffer.get());

		_release();

		m_Size = size;
		m_Buffer = new_buffer.get();
		m_IsOwner = true;		// We just made a new buffer, its now owned by the buffer

		new_buffer.release(); // The buffer now owns the pointer
	} catch(const std::bad_alloc&) {
		throw OutOfMemoryError();
	}
}

template<typename T>
burst::Buffer<T> burst::Buffer<T>::ensure_ownership()
{
	if(m_IsOwner) {
		return *this;
	} else {
		return Buffer(m_Size, _create_and_copy(m_Buffer, m_Size), true);
	}
}
