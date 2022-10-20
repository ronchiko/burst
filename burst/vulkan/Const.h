#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/Common.h>
#include <burst/Vulkan.h>

namespace burst::vulkan {
	constexpr const char* ENGINE_NAME = "Burst";
	constexpr burst::u32 ENGINE_VERSION = version(0, 1, 0);
	
	constexpr VkApplicationInfo APPLICATION_INFO{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pEngineName = ENGINE_NAME,
		.engineVersion = ENGINE_VERSION,
		.apiVersion = VK_API_VERSION_1_1
	};
}
