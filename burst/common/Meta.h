#pragma once

#include <sstream>
#include <vector>
#include <limits>
#include <functional>

#include "Types.h"
#include "Concepts.h"

namespace burst {

	/**
	 * Gives the const modifier to a type if another has the modifer.
	 */
	template<typename Original, typename New>
	using KeepConst = std::conditional_t<
		std::is_const_v<Original>,
		std::add_const_t<New>,
		New
	>;

	constexpr void _concat(std::stringstream&) {}

	template<typename T, typename... U>
	constexpr void _concat(std::stringstream& stream, const T& value, U... args) {
		stream << value;
		_concat(stream, args...);
	}

	/**
	 * @brief: Concats a group of values into a string
	 */
	template<typename... T>
	constexpr std::string concat(const T&... args) {
		std::stringstream stream;
		_concat(stream, args...);

		return stream.str();
	}

	/**
	 * Enables a bit in a u32
	 */
	constexpr u32 bit(u8 digit) {
		return 1 << digit;
	}

	/**
	 * Enables all the bits up to n fo a u32
	 */
	constexpr u32 bits(u8 n) {
		if (n >= 32) {
			return std::numeric_limits<u32>::max();
		}

		u32 number = 0;
		for (; n > 0; --n) {
			number |= bit(n - 1);
		}

		return number;
	}

	template<typename T, typename U>
	constexpr U default_convertor(const T& item) {
		return static_cast<U>(item);
	}

	/**
	 * Converts a vector of type to a vector of another type
	 */
	template<typename T, typename U>
	constexpr std::vector<U> convert(
		const std::vector<T>& source, 
		const std::function<U(const T&)> convertor = default_convertor<T, U>)
	{
		std::vector<U> dest(source.size());
		for (const auto& item : source) {
			dest.push_back(convertor(item));
		}

		return dest;
	}

	/**
	 * Converts one type of iteratable to another.
	 * 
	 * \param source: The iterable to convert from
	 */
	template<IterableConstructable To, Iterable From>
	constexpr To iter_convert(const From& source) {
		return To(source.begin(), source.end());
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
	UniqueVector<E> pull_children_of(UniqueVector<T>& base) {
		UniqueVector<E> new_vector;

		for (auto item = base.begin(); item < base.end();) {
			E* converted = dynamic_cast<E*>(item->get());
			if (nullptr != converted) {
				item->release();
				
				new_vector.push_back(std::unique_ptr<E>(converted));
				item = base.erase(item);
			}
			else {
				++item;
			}
		}

		return new_vector;
	}
};




