#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/Common/Types.h>
#include <burst/Vulkan.h>

namespace burst::vulkan {
	// The name of the engine in ASCII
	constexpr const char* ENGINE_NAME = "Burst";
	// The version of the engine
	constexpr burst::u32 ENGINE_VERSION = Version(0, 1, 0).to_u32();
	
	// The default application info for this engines version
	constexpr VkApplicationInfo APPLICATION_INFO{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pEngineName = ENGINE_NAME,
		.engineVersion = ENGINE_VERSION,
		.apiVersion = VK_API_VERSION_1_1
	};
}
