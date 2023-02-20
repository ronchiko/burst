#pragma once

#include "../traits/iterable.h"

namespace burst {

	template<typename T>
	class RangedIterable
	{
	public:
		/**
		 * Creates a new ranged iterable.
		 *
		 * \param start: The start of the range
		 * \param end: The end of the range
		 */
		constexpr RangedIterable(T start, T end)
			: m_Begin(std::move(start))
			, m_End(std::move(end))
		{}

		/**
		 * The start of the iterable.
		 */
		constexpr T begin() const
		{
			return m_Begin;
		}

		/**
		 * The end of the iterable.
		 */
		constexpr T end() const
		{
			return m_End;
		}

	private:
		T m_Begin;
		T m_End;
	};

	// Ensure we keep up with our defenition of an iterable
	static_assert(burst::iterable<RangedIterable<dummy_iterator_t>>,
				  "burst::RangedIterable must be an iterable");
}
