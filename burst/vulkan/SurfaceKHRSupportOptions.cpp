#include "SurfaceKHRSupportOptions.h"

#include <vulkan/vulkan.h>

burst::vulkan::SurfaceKHRSupportOptions burst::vulkan::SurfaceKHRSupportOptions::query(
	VkSurfaceKHR surface,
	const vk::PhysicalDevice& device
) {
	SurfaceKHRSupportOptions support_options;
	support_options.capabilities = device.getSurfaceCapabilitiesKHR(surface);

	
	support_options.formats = device.getSurfaceFormatsKHR(surface);
	support_options.present_modes = device.getSurfacePresentModesKHR(surface);

	return support_options;
}

bool burst::vulkan::SurfaceKHRSupportOptions::is_valid() const {
	return !formats.empty() && !present_modes.empty();
}