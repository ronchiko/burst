#pragma once

#include "../../Types.h"

#include "iterable.h"

namespace burst {
	
	/**
	 * Gives basic traits about a container.
	 */
	template<typename Container>
	struct container_traits;

#pragma region burst::container_traits<T> specilizations 

	template<typename T>
	struct container_traits<Vector<T>>
	{
		using element_type = T;
		using container_type = Vector<T>;
	};

	template<typename T, size_t Size>
	struct container_traits<Array<T, Size>>
	{
		using element_type = T;
		using container_type = Array<T, Size>;
	};

	template<typename T>
	struct container_traits<Set<T>>
	{
		using element_type = T;
		using container_type = Set<T>;
	};

	template<typename T, typename K>
	struct container_traits<Map<T, K>>
	{
		using element_type = Pair<T, K>;
		using container_type = Map<T, K>;
	};

#pragma endregion
	/**
	 * The requirements for a container.
	 */
	template<typename T>
	concept container = burst::iterable<T>;

	/**
	 * The element type inside a container.
	 */
	template<typename T>
	using container_element_t = 
		burst::container_traits<std::remove_cvref_t<T>>::element_type;
}
