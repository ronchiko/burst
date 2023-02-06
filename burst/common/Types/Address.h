#pragma once

#include <cstddef>

namespace burst {

	/**
	 * Pointer type wrapper.
	 */
	template<typename T>
	class Address
	{
	public:
		constexpr Address()
			: m_Data(nullptr)
		{}

		constexpr Address(std::nullptr_t)
			: Address()
		{}

		constexpr Address(T *data)
			: m_Data(data)
		{}

		/**
		 * Returns true if the pointer is not null.
		 */
		constexpr bool is_ok() const
		{
			return nullptr != m_Data;
		}

		constexpr T *operator->() const
		{
			return m_Data;
		}

		constexpr const T& operator*() const {
			return *m_Data;
		}

		constexpr T& operator*() {
			return *m_Data;
		}

		/**
		 * Casts this pointer to a pointer of a diffrent type.
		 * 
		 * \return: A new pointer object with a different type
		 */
		template<typename E>
		constexpr Address<E> cast() const
		{
			return Address(reinterpret_cast<E *>(m_Data));
		}

	private:
		T *m_Data;
	};
}
