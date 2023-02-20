#pragma once

#include "../../Types.h"


namespace burst {
	/**
	 * An iterator over a numerical range.
	 * 
	 * \tparam T: An integral to iterator over
	 */
	template<std::integral T>
	class IndexIterator
	{
	public:
		/**
		 * Creates a new indexed iterator.
		 * 
		 * \param index: The index of the iterator
		 * \param jump: The difference in index between each advancement
		 */
		constexpr explicit IndexIterator(T index, T jump = 1)
			: m_Index(index)
			, m_Jump(jump)
		{}

		/**
		 * Gets the current index of the iterator.
		 */
		constexpr T operator*() const {
			return m_Index;
		}

		/**
		 * Advances this index iterator.
		 */
		constexpr IndexIterator<T>& operator++() {
			m_Index += m_Jump;

			return *this;
		}

		/**
		 * Advances this iterator and returns an iterator with its previous index.
		 */
		constexpr IndexIterator<T> operator++(int) const {
			auto result = IndexIterator<T>(m_Index);
			m_Index += m_Jump;

			return result;
		}

		/**
		 * Checks if this iterator is the same as another.
		 */
		constexpr bool operator==(const IndexIterator<T>& other) const {
			return m_Index == other.m_Index;
		}

		/**
		 * Checks if this iterator is different as another.
		 */
		constexpr bool operator!=(const IndexIterator<T>& other) const
		{
			return m_Index != other.m_Index;
		}

	private:
		T m_Index;
		T m_Jump;
	};

	static_assert(burst::iterator<IndexIterator<u32>>,
				  "Index iterator must be follow the iterator concept");
}
