#pragma once

#define INTERFACE class
#define IFACE_FUNC(fnc) virtual fnc = 0
#define IFACE_DESTRUCTOR(cls) virtual ~cls() = default

#define IFACE_EXT(iface) public iface
#define IFACE_IMPL(func) virtual func override

// Ease of use macros
#define ENUM enum class