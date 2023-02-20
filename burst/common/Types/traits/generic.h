#pragma once

#include <concepts>

namespace burst {
	/**
	 * Ensure a type is castable to a different type.
	 */
	template<typename T, typename CastType>
	concept castable = requires(T object) {
						   { static_cast<CastType>(object) } -> std::same_as<CastType>;
					   };

	/**
	 * A class that can be accessed with the [] operator.
	 */
	template<typename T, typename IndexType>
	concept accessable = requires(T result, IndexType index) {
							 { result[index] };
						 };

	template<typename T>
	concept abstract = std::is_abstract_v<T>;
}