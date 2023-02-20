#pragma once

#include <type_traits>

namespace burst {
	template<typename T>
	concept function = std::is_function_v<T>;

	template<typename>
	struct function_traits;

	template<typename Return, typename... Args>
	struct function_traits<Return (*)(Args...)>
	{
		using return_type = Return;

		static constexpr size_t argument_count = sizeof...(Args);
	};

	template<typename Return, typename... Args>
	struct function_traits<Return (Args...)>
	{
		using return_type = Return;

		static constexpr size_t argument_count = sizeof...(Args);
	};
}
