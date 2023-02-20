#pragma once

#include "../../Types.h"

#include "RangedIterable.h"

namespace burst {

	/**
	 * An iterator that ties two iterators togther.
	 */
	template<typename Tx, typename Ty>
	class TiedIterator
	{
	public:
		constexpr TiedIterator(Tx first, Ty second)
			: m_First(std::move(first))
			, m_Second(std::move(second))
		{}

		constexpr auto operator*() const
		{
			return std::make_pair(*m_First, *m_Second);
		}

		constexpr TiedIterator<Tx, Ty>& operator++()
		{
			++m_First;
			++m_Second;

			return *this;
		}

		constexpr TiedIterator<Tx, Ty> operator++(int) const
		{
			return TiedIterator<Tx, Ty>(m_First++, m_Second++);
		}

		constexpr bool operator==(const TiedIterator<Tx, Ty>& other) const
		{
			return m_First == other.m_First && m_Second == other.m_Second;
		}

		constexpr bool operator!=(const TiedIterator<Tx, Ty>& other) const
		{
			return m_First != other.m_First || m_Second != other.m_Second;
		}

	private:
		Tx m_First;
		Ty m_Second;
	};

	// Up to date check!
	static_assert(burst::iterator<TiedIterator<dummy_iterator_t, dummy_iterator_t>>,
				  "burst::TiedIterator must follow burst::iterator concept");
}
