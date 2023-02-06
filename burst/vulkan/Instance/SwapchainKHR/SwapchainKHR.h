#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Presentables/IWindow.h>

#include "../../Configuration.h"
#include "../../Gfx/IImage.h"


namespace burst::vulkan {

	class Device;
	class GpuSurfaceBinding;
	class Queues;

	class ImageView;

	class SwapchainKHR
	{
	public:
		/**
		 * Creates a new Swapchain component using a device.
		 *
		 * \param device: The device this swapchain is bound to
		 * \param surface: The surface to create this swapchain for
		 * \param window: The window this swapchain uses
		 * \param queues: The gpu queues for this instance
		 * \param config: The configuration to use
		 * 
		 * \return: The newly created swapchain
		 */
		static SwapchainKHR create(Device& device,
								   GpuSurfaceBinding& surface,
								   IWindow& window,
								   Queues& queues,
								   const Configuration& config);

		/**
		 * The height of the image.
		 */
		u32 width() const;

		/**
		 * The width of the swapchain.
		 */
		u32 height() const;

		/**
		 * The format of the surface.
		 */
		vk::SurfaceFormatKHR format() const;

		/**
		 * Creates a vector of images from this swapchain.
		 * 
		 * \return The vector of images
		 */
		Vector<Unique<IImage>> create_images() const;

	private:
		struct Cache
		{
			vk::SurfaceCapabilitiesKHR capabilities;
			vk::SurfaceFormatKHR format;
			vk::PresentModeKHR present_mode;
			vk::Extent2D swap_extent;
			u32 image_count;
			Vector<u32> queues_family_indecies;
		};

		static vk::raii::SwapchainKHR
		create_swapchain_khr(Device& device,
							 const SurfaceKHR& surface,
							 const Cache& cache,
							 const Configuration& config);

		/**
		 * Creates a swapchain from a vk::raii::SwapchainKHR.
		 */
		explicit SwapchainKHR(vk::raii::SwapchainKHR swapchain, Cache cache);

		vk::raii::SwapchainKHR m_Swapchain;
		Cache m_Cache;
	};
}
