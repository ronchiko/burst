#pragma once

#include <functional>

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Types/Notifier.h>

#include <burst/common/Presentables/IFullscreenPresentable.h>
#include <burst/common/Presentables/IScalingPresentable.h>
#include <burst/common/Presentables/IWindow.h>

#include "../../Configuration.h"
#include "../../Gfx/IImage.h"

#include "../../Sync/Semaphore.h"
#include "../../Utils/DeviceBound.h"

#include "ISwapchainObserver.h"
#include "SwapchainCreator.h"

namespace burst::vulkan {

	class Device;
	class GpuSurfaceBinding;
	class Queues;

	class SwapchainKHR : public mix::DeviceBound,
						 public IScalingPresentableListener,
						 public IFullscreenPresentableListener
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
		static Unique<SwapchainKHR> create(Device& device,
										   GpuSurfaceBinding& surface,
										   IPresentable& window,
										   Queues& queues,
										   Shared<Configuration> config);

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
		 *
		 * \param wait_semaphore: The semaphore to wait on
		 * \param timeout: The timeout to wait on that semaphore
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
		 * Recreates this swapchain
		 */
		void force_recreation();

		virtual void on_scale_changed(u32 width, u32 height) override;
		virtual void on_fullscreen_mode_changed(FullscreenMode mode) override;

	private:
		friend class SwapchainCreator;


		/**
		 * Creates a swapchain from a vk::raii::SwapchainKHR.
		 */
		explicit SwapchainKHR(Device& device,
							  Unique<SwapchainCreator> creator,
							  vk::raii::SwapchainKHR swapchain,
							  SwapchainCache cache,
							  IPresentable& presentable);

		vk::raii::SwapchainKHR m_Swapchain;
		Unique<SwapchainCreator> m_Creator;
		SwapchainCache m_Cache;

		Notifier<ISwapchainObserver> m_Observers;
		Vector<Subscription> m_ResizeSubscriptions{};
	
		bool m_WasRescaled;
	};
}
