#pragma once

#include <burst/Common.h>

#include <burst/vulkan/Configuration.h>
#include <burst/vulkan/IVulkanWindow.h>

namespace burst::vulkan {

	/**
	 * Loads the default instance for vulkan
	 */
	Unique<IRenderer> create_vulkan_render(const ApplicationInfo& info,
										   const Configuration& configuration,
										   IVulkanWindow& window);
}
