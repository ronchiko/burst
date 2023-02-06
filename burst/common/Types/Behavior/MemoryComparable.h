#pragma once

#include "../../Meta.h"

namespace burst {

	/**
	 * A class attribute that allows a class to be compared to a diffrent class.
	 * of its kind using their raw memory
	 */
	template<typename BaseType>
	struct MemoryComparable : public BaseType
	{
	public:
		MemoryComparable(const BaseType& o)
			: BaseType(o)
		{}
		
		MemoryComparable(BaseType&& o)
			: BaseType(std::move(o))
		{}

		constexpr bool operator==(const BaseType& other) const {
			return memory_identical(this, &other, sizeof(BaseType));
		}

		constexpr bool operator!=(const BaseType& other) const {
			return !memory_identical(this, &other, sizeof(BaseType));
		}
	};

}
