#pragma once

#include <functional>

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Presentables/IWindow.h>
#include <burst/common/Types/Notifier.h>

#include "../../Configuration.h"
#include "../../Gfx/IImage.h"

#include "../../Sync/Semaphore.h"
#include "../../Utils/DeviceBound.h"

#include "ISwapchainObserver.h"

namespace burst::vulkan {

	class Device;
	class GpuSurfaceBinding;
	class Queues;

	class SwapchainKHR : public mix::DeviceBound
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

		/**
		 * Convertor to SwapchainKHR.
		 */
		explicit operator vk::SwapchainKHR() const;

		/**
		 * Acquires the next image in the swapchain.
		 */
		u32 acquire_next_image(Semaphore& wait_semaphore,
							 u64 timeout = std::numeric_limits<u64>::max());

		/**
		 * Registers a new swapchain resize observer.
		 *
		 * \param observer: The observer to register
		 * 
		 * \returns: The subscription to this event.
		 */
		Subscription register_observer(ISwapchainObserver *observer);

		/**
		 * Notifies all observers that resize occured.
		 */
		void notify_resize_happend();

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
		_create_swapchain_khr(Device& device,
							  const SurfaceKHR& surface,
							  const Cache& cache,
							  const Configuration& config);

		/**
		 * Creates a swapchain from a vk::raii::SwapchainKHR.
		 */
		explicit SwapchainKHR(Device& device,
							  vk::raii::SwapchainKHR swapchain,
							  Cache cache);

		vk::raii::SwapchainKHR m_Swapchain;
		Notifier<ISwapchainObserver> m_Observers;

		Cache m_Cache;
	};
}
