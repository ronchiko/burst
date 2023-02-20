#pragma once

#include <concepts>
#include <type_traits>

namespace burst {

	/**
	 * A pointer type.
	 */
	template<typename T>
	concept Pointer = std::is_pointer<T>::value;
}

#include "Types/traits/generic.h"
#include "Types/traits/iterable.h"
#include "Types/traits/container.h"

#include "Types/traits/function.h"
#include "Types/traits/member_function.h"