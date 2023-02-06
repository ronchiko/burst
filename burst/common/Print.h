#pragma once

#include "Types.h"
#include "Concepts.h"

namespace burst {
	
	constexpr const char *DEFAULT_ITEM_PREFIX = "* ";

	/**
	 * Creates a pretty string of an iterable.
	 * 
	 * \param iterable: The iterable to pretty string
	 * \param item_prefix: The prefix for each item
	 * \param indent: The indent of each item (in spaces)
	 * 
	 * \return: The pretty string
	 */
	template<typename T> requires Iterable<T>
	constexpr String pretty_iterable(
		const T& iterable, cstr item_prefix = DEFAULT_ITEM_PREFIX, u32 indent = 1)
	{
		std::stringstream ss;

		for (const auto& element : iterable) {
			for(int i = 0; i < indent; ++i)
				ss << " ";

			ss << item_prefix << element << std::endl;
		}

		return ss.str();
	}

}
