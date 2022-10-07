#pragma once

#include <array>

#include <vulkan/vulkan.h>

#include <burst/Common.h>

namespace burst::vulkan {

	constexpr VkAllocationCallbacks* NO_ALLOCATOR = nullptr;

	constexpr std::array<burst::cstr, 1> REQUIRED_VALIDATION_LAYERS = {
		"VK_LAYER_KHRONOS_validation"
	};

	/*
	 * Throws an exception if validation layers are not available 
	 */
	void assert_validation_layer_available(const std::vector<cstr>&);
}
