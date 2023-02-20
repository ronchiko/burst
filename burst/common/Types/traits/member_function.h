#pragma once

#include <type_traits>

namespace burst {

	template<typename>
	struct is_member_function : public std::false_type
	{};

	template<typename Return, typename Object, typename... Args>
	struct is_member_function<Return (Object::*)(Args...)> : public std::true_type
	{};

	template<typename T>
	concept member_function = is_member_function<T>::value;

	template<typename>
	struct member_function_traits;

	template<typename Return, typename Object, typename... Args>
	struct member_function_traits<Return (Object::*)(Args...)>
	{
		using return_type = Return;
		using object_type = Object;
	
		constexpr static size_t argument_count = sizeof...(Args);
	};
}
