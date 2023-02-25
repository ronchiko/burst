#pragma once

#include <burst/common/Application.h>

#include <burst/vulkan/Configuration.h>
#include <burst/vulkan/IVulkanWindow.h>

namespace burst::vulkan {

	/**
	 * Loads the default instance for vulkan
	 */
	Unique<IRenderer> create_vulkan_render(const ApplicationInfo& info,
										   Shared<Configuration> configuration,
										   IVulkanWindow& window);
}
