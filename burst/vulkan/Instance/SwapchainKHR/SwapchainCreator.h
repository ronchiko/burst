#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Presentables/IPresentable.h>

#include "../../Configuration.h"
#include "../SurfaceKHR/GpuSurface.h"

namespace burst::vulkan {
	class Device;
	class Queues;

	struct SwapchainCache
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		vk::SurfaceFormatKHR format;
		vk::PresentModeKHR present_mode;
		vk::Extent2D swap_extent;
		u32 image_count;
		Vector<u32> queues_family_indecies;
	};

	/**
	 * A class for creating and swapchain using a context.
	 * 
	 * Primarly used to recreate the swapchain once the window has changed
	 */
	class SwapchainCreator
	{
	public:
		/**
		 * \see burst::vulkan::SwapchainKHR::create
		 */
		explicit SwapchainCreator(GpuSurfaceBinding& surface,
								  IPresentable& window,
								  Queues& queues,
								  Shared<Configuration> config);

		/**
		 * Creates a new swapchain from a device.
		 *
		 * \param device: The device to bind the swapchain to
		 */
		Pair<vk::raii::SwapchainKHR, SwapchainCache> create(Device& device);

		u32 last_width() const;
		u32 last_height() const;

	private:
		vk::raii::SwapchainKHR
		_create_swapchain_khr(Device& device, const SwapchainCache& cache);

		GpuSurfaceBinding m_Surface;
		IPresentable& m_Presentable;
		Queues& m_Queues;
		Shared<Configuration> m_Configuration;
	};
}
