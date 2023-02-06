#pragma once

#include "../../Types.h"

namespace burst {
	
	/**
	 * Behavior class for enum utilities.
	 * 
	 * \param T: The base enumator type
	 */
	template<typename T>
	class Enum
	{
	public:

		// Constructor from u32
		constexpr Enum(T value)
			: m_Value(value)
		{}

		// Constructor from u32
		constexpr Enum(u32 value)
			: m_Value(static_cast<T>(value))
		{}

		// Convertor to the base enum type
		constexpr operator T() const
		{
			return m_Value;
		}

		// Convertor to u32
		constexpr operator u32() const
		{
			return static_cast<u32>(m_Value);
		}

	private:
		T m_Value;
	};

	/**
	 * An enum that can be converted implicitly between two types
	 */
	template<typename T, typename E>
	union UnionEnum
	{
	public:
		constexpr UnionEnum(T value)
			: m_First(value)
		{}

		constexpr UnionEnum(E value)
			: m_Second(value)
		{}

		constexpr operator T() const {
			return static_cast<T>(m_First);
		}

		constexpr operator E() const {
			return static_cast<E>(m_Second);
		}

	private:
		Enum<T> m_First;
		Enum<E> m_Second;
	};
}
