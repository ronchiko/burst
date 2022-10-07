#pragma once

#include <sstream>
#include <vector>
#include <limits>
#include <functional>

#include "Types.h"

namespace burst {
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

};
