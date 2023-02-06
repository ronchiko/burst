#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {

	struct SurfaceSupportOptions
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		Vector<vk::SurfaceFormatKHR> formats;
		Vector<vk::PresentModeKHR> present_modes;

		/**
		 * Checks if the surface support options are ok.
		 * 
		 * \return: The if the support options are ok
		 */
		bool is_ok() const;
	};

}
