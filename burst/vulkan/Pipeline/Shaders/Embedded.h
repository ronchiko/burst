#pragma once

/**
 * Auto generated embedded shader linkage.
 */

// NOLINTBEGIN

#include "Loaders/BuiltinShader.h"

#include <burst/common/Types.h>
#include <burst/common/Types/Buffer.h>


#define EMBEDDED_SHADER(name)                                                       \
	extern "C" extern char name##_BUFFER[];                                         \
	extern "C" extern size_t name##_SIZE;                                           \
	inline static ::burst::Buffer<char> name##_DATA_BUFFER{                         \
		name##_BUFFER, static_cast<burst::u32>(name##_SIZE)                         \
	};

EMBEDDED_SHADER(VERTEX_SHADER);

EMBEDDED_SHADER(FRAGMENT_SHADER);

namespace burst::vulkan {
	extern Unique<BuiltinShader> g_DefaultVertexShader;
	extern Unique<BuiltinShader> g_DefaultFragmentShader;
}

// NOLINTEND