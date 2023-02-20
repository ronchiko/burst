#include "SwapchainBound.h"

#include "../Instance/SwapchainKHR/SwapchainKHR.h"

namespace burst::vulkan::mix {
	SwapchainBound::SwapchainBound(SwapchainKHR& swapchain)
		: m_Swapchain(swapchain)
	{}

	vk::SwapchainKHR SwapchainBound::swapchain() const {
		return static_cast<vk::SwapchainKHR>(m_Swapchain);
	}
}
