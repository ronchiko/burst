#pragma once

namespace burst::vulkan {
	class SwapchainKHR;

	/**
	 * Interface for listening for swapchain event.
	 */
	class ISwapchainObserver
	{
	public:
		virtual ~ISwapchainObserver() = default;

		/**
		 * Invoked when the a swapchain is resized.
		 * 
		 * \param swapchain: The swapchain that was resized
		 */
		virtual void on_swapchain_resized(const SwapchainKHR& swapchain) = 0;
	};
}
