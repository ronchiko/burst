#pragma once

#include "RangedIterable.h"

#include "IndexIterator.h"
#include "TiedIterator.h"

namespace burst {

	/**
	 * Skips to the next item relative to the iterator.
	 *
	 * \param iter: The reference iterator
	 * \param diff: The amount to skip
	 * \return: The iterator that was skipped to
	 */
	template<typename T>
	constexpr T skip(const T& iter, i32 diff)
	{
		T result = iter;
		::std::advance(result, diff);

		return result;
	}

	/**
	 * Warps an iterable with an iterable that pairs each element with its index
	 *
	 * \param iterable: The iterable to warp
	 * \return
	 */
	template<burst::iterable T>
	constexpr auto index(T& iterable) -> RangedIterable<
		TiedIterator<IndexIterator<u32>, decltype(iterable.begin())>>
	{
		using It = decltype(iterable.begin());
		using U = TiedIterator<IndexIterator<u32>, It>;

		U begin(IndexIterator<u32>(0), iterable.begin());

		auto size =
			static_cast<u32>(::std::distance(iterable.begin(), iterable.end()));
		auto end = skip(begin, size);

		return RangedIterable<U>(std::move(begin), std::move(end));
	}

	/**
	 * Index method for r-values.
	 * 
	 * \param iterable: The r-value iterable
	 */
	template<burst::iterable T>
	constexpr auto index(T&& iterable)
	{
		// R-Value implemenatation of the index, Move the iterable into an
		// opaque object that contains the R-Value to prevent it from being
		// destroyed.
		using It = decltype(iterable.begin());
		using U = TiedIterator<IndexIterator<u32>, It>;

		struct Object
		{
			T base;
			RangedIterable<U> iter;

			constexpr auto begin() const
			{
				return iter.begin();
			}

			constexpr auto end() const
			{
				return iter.end();
			}
		};

		// Creates a dummy tied iterator for creation
		U dummy{ IndexIterator<u32>{ 0 }, iterable.end() };

		Object obj{
			::std::move(iterable),
			{ dummy, dummy },
		};

		obj.iter = index(obj.base); // Index with an L-Value
		return obj;
	}

	/**
	 * Zips two iterables togther
	 *
	 * \param a: The first iterable
	 * \param b: The second iterable
	 */
	template<burst::iterable A, burst::iterable B>
	constexpr auto zip(const A& a, const B& b)
	{
		using T = TiedIterator<decltype(a.begin()), decltype(b.begin())>;

		auto distance_a = static_cast<u32>(std::distance(a.begin(), a.end()));
		auto distance_b = static_cast<u32>(std::distance(b.begin(), b.end()));

		auto distance = std::min(distance_a, distance_b);

		return RangedIterable<T>(
			T(a.begin(), b.begin()),
			T(skip(a.begin(), distance), skip(b.begin(), distance)));
	}
}
