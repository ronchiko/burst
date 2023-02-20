#pragma once

#include <concepts>

namespace burst {
	
	// Dummy type for iterators
	using dummy_iterator_t = std::vector<char>::iterator;

	/**
	 * What burst treats as an iterator.
	 */
	template<typename T>
	concept iterator = requires(T object) {
						   // Increment
						   { ++object } -> std::same_as<T&>;
						   { object++ } -> std::same_as<T>;
						   // Comparison
						   { object != object } -> std::same_as<bool>;
						   { object == object } -> std::same_as<bool>;
						   { *object };		// We dont need to worry what the type of base type of the iterator is
					   };
	
	/**
	 * An object with a begin & end functions
	 */
	template<typename T>
	concept iterable = requires(T a) {
						   { a.begin() } -> burst::iterator;
						   { a.end() } -> burst::iterator;
					   };

	/**
	 * An object that can be constructed by an a start and end iterators.
	 */
	template<typename T>
	concept iterable_constructible = requires(T a) {
										{ T(a.begin(), a.end()) } -> std::same_as<T>;
									 };

}
