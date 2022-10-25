#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Const.h"

namespace burst {
	// Primitive types
	using u8 = uint8_t;
	using i8 = int8_t;

	using u16 = uint16_t;
	using i16 = int16_t;

	using i32 = int32_t;
	using u32 = uint32_t;

	using i64 = int64_t;
	using u64 = uint64_t;

	using f32 = float;
	using f64 = double;

	// Standard types
	using size = size_t;
	using uid = u64;

	using cstr = const char*;
	using cwstr = const wchar_t*;

	using CStrVector = std::vector<cstr>;

	template<typename T>
	using UniqueVector = std::vector<std::unique_ptr<T>>;

	template<typename T>
	using IdMap = std::unordered_map<uid, T>;

	// Vectored types
	using vec2 = glm::vec<2, f32, glm::defaultp>;
	using vec3 = glm::vec<3, f32, glm::defaultp>;
	using vec4 = glm::vec<4, f32, glm::defaultp>;

	using int2 = glm::vec<2, i32, glm::defaultp>;
	using int3 = glm::vec<3, i32, glm::defaultp>;

	using mat2x2 = glm::mat<2, 2, f32, glm::defaultp>;
	using mat3x3 = glm::mat<3, 3, f32, glm::defaultp>;
	using mat4x4 = glm::mat<4, 4, f32, glm::defaultp>;
}