#pragma once

#include <stdexcept>

#define INTERFACE			  class
#define IFACE_FUNC(fnc)		  virtual fnc = 0
#define IFACE_DESTRUCTOR(cls) virtual ~cls() = default

#define IFACE_EXT(iface)                                                            \
public                                                                              \
	iface
#define IFACE_IMPL(func) virtual func override

// Ease of use macros
#define ENUM enum class

#define ENUM_LAST _LastValue

#ifdef _DEBUG
#define ASSERT(expr, msg)                                                           \
	if(!(expr)) {                                                                   \
		::burst::log::error("Assertion Error: (" #expr ") isn't true: " #msg);      \
		throw ::std::exception("Assertion Error!");                                 \
	}

// Same as assert but for calls with side effects
#define CHECK(expr, msg) ASSERT(expr, msg)

/**
 * In release mode, exceutes this operation, in debug mode rethrow the exception.
 *
 * \note: Use inside catch blocks only!
 */
#define FALLBACK(expr) throw
#else

#define FALLBACK(expr) (expr)
#define CHECK(expr)	   (expr)
#define ASSERT(expr, msg)
#endif

/**
 * Like assert but doesnt throw an expcetion and print a warning
 */
#define WASSERT(expr, msg)                                                          \
	if(!(expr)) {                                                                   \
		::burst::log::warning("Assertion Warning: (" #expr ") isn't true: " #msg);  \
	}

// Put inside a class to delete its copy constructors
#define NOT_COPIABLE(cls)                                                           \
	cls(const cls&) = delete;                                                       \
	cls& operator=(const cls&) = delete;

// Put inside a class to delete its move contructors
#define NOT_MOVABLE(cls)                                                            \
	cls(cls&&) = delete;                                                            \
	cls& operator=(cls&&) = delete;
