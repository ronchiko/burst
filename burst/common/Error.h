#pragma once

#include <stdexcept>

#include "Meta.h"

namespace burst {
	template<typename... T>
	constexpr String concat(const T&...);

	using Error = std::exception;

	/**
	 * An error whos error must be computed at runtime.
	 */
	class RuntimeError : public std::runtime_error {
	public:		
		explicit RuntimeError(const String& message);
	
		template<typename... T>
		static RuntimeError make(const T&... args) {
			return RuntimeError(::burst::concat(args...));
		}
	};

	/**
	 * An error whos message can be known at compile time.
	 */
	class StaticError : public Error {
	public:
		explicit StaticError(cstr message);
	};
	
	/**
	 * An error that occurs when an attempt to access nullptr happens.
	 */
	class NullptrError : public StaticError {
	public:
		explicit NullptrError(cstr message);
	};

	/**
	 * An error that occurs when a file is not found.
	 */
	class FileNotFoundError : public RuntimeError {
	public:
		explicit FileNotFoundError(const String& name);
	};

	class OutOfMemoryError : public StaticError
	{
	public:
		inline OutOfMemoryError()
			: StaticError("Out Of Memory")
		{}
	};
}

/**
 * Creates an inlined exception implementation.
 * 
 * \param name: The name of the exception
 * \param message: The message to show when this exception is raised
 */
#define INLINE_XCEPTION(name, message)                                                             \
	class name : public ::burst::StaticError                                                       \
	{                                                                                              \
	public:                                                                                        \
		inline name()                                                                              \
			: ::burst::StaticError(message)                                                        \
		{}                                                                                         \
	}
