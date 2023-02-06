#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <span>
#include <array>
#include <optional>
#include <memory>
#include <set>
#include <map>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Const.h"

namespace burst {
	// NOLINTBEGIN
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
	// NOLINTEND

	// Vectored types
	using Vec2 = glm::vec<2, f32, glm::defaultp>;
	using Vec3 = glm::vec<3, f32, glm::defaultp>;
	using Vec4 = glm::vec<4, f32, glm::defaultp>;

	using Int2 = glm::vec<2, i32, glm::defaultp>;
	using Int3 = glm::vec<3, i32, glm::defaultp>;

	using Uint2 = glm::vec<2, u32, glm::defaultp>;

	using Mat2x2 = glm::mat<2, 2, f32, glm::defaultp>;
	using Mat3x3 = glm::mat<3, 3, f32, glm::defaultp>;
	using Mat4x4 = glm::mat<4, 4, f32, glm::defaultp>;

	template<typename T>
	using Optional = std::optional<T>;

	template<typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename T>
	using Ref = std::reference_wrapper<T>;

	template<typename T, u32 Size>
	using Array = std::array<T, Size>;

	template<typename T>
	using Vector = std::vector<T>;

	template<typename T>
	using List = std::list<T>;

	template<typename T>
	using Set = std::set<T>;

	template<typename K, typename V>
	using HashMap = std::unordered_map<K, V>;

	template<typename K, typename V>
	using Map = std::map<K, V>;

	template<typename K, typename V>
	using Multimap = std::multimap<K, V>;

	template<typename T, typename E>
	using Pair = std::pair<T, E>;

	template<typename T>
	using Span = std::span<T>;

	using CStrVector = Vector<cstr>;

	using String = std::string;
	
	template<typename T>
	using UniqueVector = Vector<Unique<T>>;

	template<typename T>
	using IdMap = HashMap<uid, T>;

}

#include "Error.h"

/**
 * Casts an object to its non const counterpart.
 * 
 * \param value: The value cast
 * 
 * \note: Avoid using this macro unless nessacary.
 */
#define CONST_PROXY(value) const_cast<::std::remove_const_t<decltype(value)>>(value)

/**
 * Gets the address of the of an optional value if it has a value.
 * 
 * \param opt: The optional value
 */
#define GET_ADDRESS(opt) ((opt).has_value() ? &(opt).value() : nullptr)


