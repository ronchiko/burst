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

	template<typename T>
	concept IterableConstructable = requires(T a) {
		{ T(a.begin(), a.end()) } -> std::same_as<T>;
	};

	template<typename T>
	concept Map = requires(T map) {
		{ (*map.begin()).first } -> std::same_as<typename T::key_type>;
		{ (*map.begin()).second } -> std::same_as<typename T::value_type>;
	};
}
