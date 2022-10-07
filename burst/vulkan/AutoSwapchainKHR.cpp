#include "SwapchainKHR.h"

namespace burst::vulkan {

	AutoSwapchainKHR::AutoSwapchainKHR(nullptr_t) :
		Base(nullptr), m_Device(nullptr), m_Extent(), m_Format(), m_ImageViews{}
	{}
	
	AutoSwapchainKHR::AutoSwapchainKHR(VkSwapchainKHR swapchain, CreateInfo info) :
		Base(swapchain, SwapchainKHRDeleter{ info.device }),
		m_Device(info.device),
		m_Extent(info.extent),
		m_Format(info.format),
		m_ImageViews{}
	{
		u32 swapchain_length = 0;
		vkGetSwapchainImagesKHR(m_Device, get(), &swapchain_length, nullptr);

		std::vector<VkImage> images(swapchain_length);
		vkGetSwapchainImagesKHR(m_Device, get(), &swapchain_length, images.data());

		m_ImageViews.reserve(images.size());
		for (const auto& image : images) {
			m_ImageViews.push_back(ImageView(m_Device, image, m_Format.format));
		}
	}

	std::vector<ImageView>& AutoSwapchainKHR::get_images() {
		return m_ImageViews;
	}
}