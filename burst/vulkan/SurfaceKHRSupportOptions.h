#pragma once

#include <vulkan/vulkan.h>

#include "PhysicalDevice.h"

namespace burst::vulkan {

	struct SurfaceKHRSupportOptions
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> present_modes;
		
		/**
		 * Queries screen information about a surface 
		 */
		static SurfaceKHRSupportOptions query(VkSurfaceKHR surface, const vk::PhysicalDevice& device);
		
		/**
		 * Checks if the surface is valid
		 */
		bool is_valid() const;
	};
}