#pragma once

#include <vulkan/vulkan_raii.hpp>

namespace burst::vulkan {
	class SwapchainKHR;

	namespace mix {
		/**
		 * Mixin for objects that are bound to a swapchain.
		 */
		class SwapchainBound
		{
		public:
			explicit SwapchainBound(SwapchainKHR& swapchain);

		protected:
			vk::SwapchainKHR swapchain() const;

			SwapchainKHR& m_Swapchain;
		};
	}
}
