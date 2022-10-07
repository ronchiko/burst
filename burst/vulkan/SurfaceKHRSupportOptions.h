#pragma once

#include <vulkan/vulkan.h>

#include "PhysicalDevice.h"

namespace burst::vulkan {

	struct SurfaceKHRSupportOptions
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> present_modes;
		
		/**
		 * Queries screen information about a surface 
		 */
		static SurfaceKHRSupportOptions query(VkSurfaceKHR surface, const PhysicalDevice& device);
		
		/**
		 * Checks if the surface is valid
		 */
		bool is_valid() const;
	};
}