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
	using KeepConst = std::conditional_t<std::is_const_v<Original>, std::add_const_t<New>, New>;

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
	 * Converts one type of iteratable to another.
	 *
	 * \param source: The iterable to convert from
	 */
	template<IterableConstructable To, Iterable From>
	constexpr To iter_convert(const From& source)
	{
		return To(source.begin(), source.end());
	}

	/**
	 * Casts a vector into a different type (with static_cast)
	 */
	template<typename To, typename From>
	constexpr Vector<To> vec_cast(const Vector<From>& v)
	{
		Vector<To> casted;
		casted.reserve(v.size());

		for (const auto& element : v) {
			casted.push_back(static_cast<To>(element));
		}

		return casted;
	}

	/**
	 * Moves all children of an class from a vector to a new vector.
	 *
	 * \tparam E: The type of the child
	 * \tparam T: The type of the parent
	 * \return
	 */
	template<typename E, typename T>
	requires std::derived_from<E, T>

	inline UniqueVector<E> pull_children_of(UniqueVector<T>& base)
	{
		UniqueVector<E> new_vector;

		for(auto item = base.begin(); item < base.end();) {
			E *converted = dynamic_cast<E *>(item->get());
			if(nullptr != converted) {
				item->release();

				new_vector.push_back(Unique<E>(converted));
				item = base.erase(item);
			} else {
				++item;
			}
		}

		return new_vector;
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
	constexpr inline bool memory_identical(const void *left, const void *right, size_t len)
	{
		const u8 *l = static_cast<const u8 *>(left), *r = static_cast<const u8 *>(right);
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

	/**
	 * Converts a vector to vector of diffrent type.
	 *
	 * \param from: The array to convert from
	 * \param convertor: The convertor function to use
	 * \return
	 */
	template<typename To, typename From>
	Vector<To> convert(const Vector<From>& from,
		std::function<To(const From&)> convertor = default_convertor)
	{
		auto range = from | ::std::views::transform(convertor);

		return Vector<To>(range.begin(), range.end());
	}

	template<typename To, typename From>
	Vector<To> convert(Vector<From>& from,
					   std::function<To(From&)> convertor = default_convertor)
	{
		auto range = from | ::std::views::transform(convertor);

		return Vector<To>(range.begin(), range.end());
	}
};
