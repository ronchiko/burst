#pragma once

#include "Types.h"

namespace burst {
	template<typename T>
	struct Cast
	{
	public:
		template<typename E>
		constexpr Cast(E value)
			: m_Value(static_cast<T>(value))
		{}

		constexpr operator T() const {
			return m_Value;
		}

		constexpr T value() const {
			return m_Value;
		}

	private:
		T m_Value;
	};

	/**
	 * Checks if a flag is on.
	 *
	 * \param value: The value to check if a flag is active in
	 * \param flag: The flag to check if its active
	 */
	constexpr bool flag_on(u32 value, Cast<u32> flag)
	{
		return value & static_cast<u32>(flag);
	}

	/**
	 * Clears a flag from a value.
	 */
	constexpr u32 clear_flag(u32 value, Cast<u32> flag)
	{
		return value & ~flag.value();
	}
}
