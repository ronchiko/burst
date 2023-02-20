#pragma once

#include "Concepts.h"
#include "Types.h"

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
	constexpr String pretty_iterable(const burst::iterable auto& iterable,
									 cstr item_prefix = DEFAULT_ITEM_PREFIX,
									 u32 indent = 1)
	{
		std::stringstream ss;

		for(const auto& element : iterable) {
			for(u32 i = 0; i < indent; ++i)
				ss << " ";

			ss << item_prefix << element << std::endl;
		}

		return ss.str();
	}

}
