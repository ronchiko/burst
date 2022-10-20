#pragma once

#include <burst/Common.h>

#include "burst/vulkan/Instance.h"

namespace burst::vulkan {
	constexpr burst::u32 version(u8 major, burst::u16 minor, burst::u16 patch = 0) {
		constexpr u32 PATCH_BITS = burst::bits(12);
		constexpr u32 MAJOR_BITS = burst::bits(7);
		constexpr u32 MINOR_BITS = burst::bits(10);

		return
			((major & MAJOR_BITS) << 22) |
			((minor & MINOR_BITS) << 12) |
			(patch & PATCH_BITS);

	}

	/**
	 * Loads the default instance for vulkan
	 */
	Instance load_default_instance(cstr name, u32 version, Window* window);
}
