#pragma once

#include <concepts>
#include <type_traits>

namespace burst {

	/**
	 * A pointer type.
	 */
	template<typename T>
	concept Pointer = std::is_pointer<T>::value;

	/**
	 * A collection type.
	 */
	template<typename T, typename U>
	concept Collection = requires(T a)
	{
		{
			a[0]
			} -> std::same_as<U>;
		{
			a.size()
			} -> std::same_as<size_t>;
	};

	/**
	 * An object that can be iterated over.
	 */
	template<typename T>
	concept Iterable = requires(T a)
	{
		{ a.begin() };
		{ a.end() };
	};

	/**
	 * An object that can be constructed by an iterable.
	 */
	template<typename T>
	concept IterableConstructable = requires(T a)
	{
		{
			T(a.begin(), a.end())
			} -> std::same_as<T>;
	};

	/**
	 * An object that can be called with a specific set of arguments.
	 */
	template<typename T, typename Result, typename... Args>
	concept Callable = requires(T object, Args... args)
	{
		{
			object(args...)
			} -> std::same_as<Result>;
	};

	/**
	 * A callable that result can be discarded.
	 */
	template<typename T, typename... Args>
	concept DiscardableCallable = Callable<T, void, Args...>;

	/**
	 * Ensure a type is castable to a different type.
	 */
	template<typename T, typename Ty>
	concept Castable = requires(T a)
	{
		{ static_cast<Ty>(a) };
	};

	/**
	 * A class that can be accessed with the [] operator.
	 */
	template<typename T, typename IndexType>
	concept Accessable = requires(T a, IndexType b)
	{
		{ a[b] };
	};
}
