#include "SurfaceKHRSupportOptions.h"

#include <vulkan/vulkan.h>

template<class T>
using QueryFunctions = VkResult (__stdcall*)(
	VkPhysicalDevice,
	VkSurfaceKHR,
	burst::u32*,
	T*
);

template<class T>
std::vector<T> query_surface_list_info(
	VkPhysicalDevice device, 
	VkSurfaceKHR surface,
	QueryFunctions<T> func
) {
	burst::u32 count = 0;
	func(device, surface, &count, nullptr);

	std::vector<T> results(count);
	func(device, surface, &count, results.data());
	return results;
}

burst::vulkan::SurfaceKHRSupportOptions burst::vulkan::SurfaceKHRSupportOptions::query(
	VkSurfaceKHR surface,
	const PhysicalDevice& device
) {
	SurfaceKHRSupportOptions support_options;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.device(), surface, &support_options.capabilities);

	support_options.formats = query_surface_list_info<VkSurfaceFormatKHR>(
		device.device(), 
		surface, 
		vkGetPhysicalDeviceSurfaceFormatsKHR);
	support_options.present_modes = query_surface_list_info<VkPresentModeKHR>(
		device.device(), 
		surface, 
		vkGetPhysicalDeviceSurfacePresentModesKHR);

	return support_options;
}

bool burst::vulkan::SurfaceKHRSupportOptions::is_valid() const {
	return !formats.empty() && !present_modes.empty();
}