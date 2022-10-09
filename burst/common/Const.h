#pragma once

#ifdef _MSC_VER

// Macros for microsoft specific keywords
#define INTERFACE __interface
#define IFACE_FUNC(fnc) fnc;
#define IFACE_DESTRUCTOR(cls)

#define ABSTRACT abstract

#else

#define INTERFACE class
#define IFACE_FUNC(fnc) virtual fnc = 0
#define IFACE_DESTRUCTOR(cls) virtual ~cls() = default;

#define ABSTRACT

#endif

// Ease of use macros
#define ENUM enum class