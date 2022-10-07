#pragma once

#include <type_traits>
#include <concepts>

namespace burst {

	template<typename T>
	concept Pointer = std::is_pointer<T>::value;

	template<typename T, typename U>
	concept Collection = requires(T a) {
		{ a[0] }		-> std::same_as<U>;
		{ a.size() }	-> std::same_as<size_t>;
	};

	template<typename T>
	concept Iterable = requires(T a) {
		{ a.begin() };
		{ a.end() };
	};
}
