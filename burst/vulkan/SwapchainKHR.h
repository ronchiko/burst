#pragma once

#include <vulkan/vulkan.h>

#include "Component.h"
#include "ImageView.h"

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

	/**
	 * Component class for SwapchainKHR
	 */
	class SwapchainKHR {
	public:
		using Type = AutoSwapchainKHR;

		static void add_dependencies(ListComponentInfo<std::set<cstr>>&);

		static Type create_component(const ComponentCreateInfo& create_info);
	};
}
