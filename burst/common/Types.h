#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Const.h"

namespace burst {
	using u8 = uint8_t;
	using i8 = int8_t;

	using u16 = uint16_t;
	using i16 = int16_t;

	using i32 = int32_t;
	using u32 = uint32_t;

	using f32 = float;
	using f64 = double;

	using cstr = const char*;
	using cwstr = const wchar_t*;

	using CStrVector = std::vector<cstr>;
}