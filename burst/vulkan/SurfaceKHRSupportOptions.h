#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>

namespace burst::vulkan {

	struct SurfaceKHRSupportOptions
	{
		vk::SurfaceCapabilitiesKHR capabilities;
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