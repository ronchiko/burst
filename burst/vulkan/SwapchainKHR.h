#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "Component.h"
#include "ImageView.h"

#include "IDeviceComponent.h"

namespace burst::vulkan {

	/**
	 * Deleter for the Swapchain component
	 */
	struct SwapchainKHRDeleter {
		VkDevice device;

		void operator()(VkSwapchainKHR swapchain);
	};

	/**
	 * RAII owner for swap chain
	 */
	class AutoSwapchainKHR : public std::unique_ptr<
		std::remove_pointer_t<VkSwapchainKHR>,
		SwapchainKHRDeleter
	> {
	public:
		using Base = std::unique_ptr<std::remove_pointer_t<VkSwapchainKHR>, SwapchainKHRDeleter>;

		struct CreateInfo {
			VkDevice device;
			VkExtent2D extent;
			VkSurfaceFormatKHR format;
		};

		AutoSwapchainKHR(nullptr_t);

		AutoSwapchainKHR(VkSwapchainKHR, CreateInfo);

		std::vector<ImageView>& get_images();

	private:
		VkDevice m_Device;
		VkExtent2D m_Extent;
		VkSurfaceFormatKHR m_Format;
		std::vector<ImageView> m_ImageViews;
	};

	class SwapchainKHR : public IDeviceComponent {
	public:
		SwapchainKHR() = default;

		IFACE_IMPL(void add_requirements(
			InstanceRequirements&
		) const);

		IFACE_IMPL(void init(
			const vk::raii::Device& device,
			const AdditionalCreateInfo& create_info
		));

	private:
		struct Info {
			vk::Device m_Owner;
			vk::Extent2D m_Extent;
			vk::SurfaceFormatKHR m_Format;
			std::vector<vk::raii::ImageView> m_ImageViews;
		};

		vk::raii::SwapchainKHR m_Swapchain;
	};
}
