#pragma once

#include <functional>
#include <limits>
#include <ranges>
#include <sstream>
#include <vector>

#include "Concepts.h"
#include "Types.h"

namespace burst {

	/**
	 * Gives the const modifier to a type if another has the modifer.
	 */
	template<typename Original, typename New>
	using KeepConst =
		std::conditional_t<std::is_const_v<Original>, std::add_const_t<New>, New>;

	constexpr void _concat(std::stringstream&) {}

	template<typename T, typename... U>
	constexpr void _concat(std::stringstream& stream, const T& value, U... args)
	{
		stream << value;
		_concat(stream, args...);
	}

	/**
	 * @brief: Concats a group of values into a string
	 */
	template<typename... T>
	constexpr std::string concat(const T&...args)
	{
		std::stringstream stream;
		_concat(stream, args...);

		return stream.str();
	}

	/**
	 * Enables a bit in a u32
	 */
	constexpr u32 bit(u8 digit)
	{
		return 1 << digit;
	}

	/**
	 * Enables all the bits up to n fo a u32
	 */
	constexpr u32 bits(u8 n)
	{
		if(n >= 32) {
			return std::numeric_limits<u32>::max();
		}

		u32 number = 0;
		for(; n > 0; --n) {
			number |= bit(n - 1);
		}

		return number;
	}

	/**
	 * Assigns a value to a variable if the variable value is .
	 *
	 * \param value: The variable to assign to
	 * \param comapre_to: The value to compare to
	 * \param set_to: The value to set to if the values are equal
	 */
	template<typename T>
		requires std::copyable<T> && std::equality_comparable<T>
	constexpr void comapre_exchange(T& value, const T& compare_to, const T& set_to)
	{
		if(compare_to == value) {
			value = set_to;
		}
	}

	/**
	 * Tries to do an upcast of a pointer, throws an error on failure.
	 *
	 * \param base: The base object
	 */
	template<typename Child, typename Base>
	constexpr Child *force_upcast(Base *base)
	{
		auto *upper = dynamic_cast<Child *>(base);
		if(nullptr == upper) {
			throw std::exception("Failed to do forced upcast!");
		}

		return upper;
	}

	/**
	 * Checks if 2 buffer in memory are the same.
	 *
	 * \param left: The first buffer
	 * \param right: The secodn buffer
	 * \param len: The length of the buffers
	 * \return: True if they identical
	 */
	constexpr inline bool
	memory_identical(const void *left, const void *right, size_t len)
	{
		const u8 *l = static_cast<const u8 *>(left),
				 *r = static_cast<const u8 *>(right);
		for(size_t i = 0; i < len; ++i, ++l, ++r) {
			if(*l != *r) {
				return false;
			}
		}

		return true;
	}

	/**
	 * The default convertion function.
	 *
	 * \param item
	 * \return
	 */
	template<typename T, typename U>
	constexpr U default_convertor(const T& item)
	{
		return static_cast<U>(item);
	}

	// Shortcut to use when you have iterable
	template<burst::iterable From, burst::iterable To>
	constexpr auto iterable_default_convertor =
		default_convertor<burst::container_element_t<From>,
						  burst::container_element_t<To>>;

	/**
	 * Converts one type of iteratable to another.
	 *
	 * \param source: The iterable to convert from
	 *
	 * \note: Use this when trying to cast just the type of the iterator,
	 *		  if you wish to cast the type inside the container, use burst::convert
	 */
	template<burst::iterable_constructible To, burst::iterable From>
	constexpr To iter_convert(const From& source)
	{
		static_assert(
			std::is_same_v<burst::container_element_t<From>,
						   burst::container_element_t<To>>,
			"The types of the target and result iterators must be the same");


		return To(source.begin(), source.end());
	}

	/**
	 * Converts a each element of a container into a different element, of a
	 *different container
	 *
	 * \param from: The container to convert into a diffrent type
	 * \param convertor: The function to convert each element (gets the element type
	 *of from and returns the element type of To
	 *
	 * \tparam: The type to convert the vector, must follow
	 *burst::iterable_constructible
	 *
	 * \return: The converted vector
	 */
	template<burst::iterable_constructible To, burst::iterable From>
	To convert(const From& t,
			   // std::function return the element of target container type and
			   // receives a const ref of the element type of source container
			   std::function<burst::container_element_t<To>(
				   const burst::container_element_t<From>&)> convertor)
	{
		auto range = t | ::std::views::transform(convertor);
		return To(range.begin(), range.end());
	}
};
