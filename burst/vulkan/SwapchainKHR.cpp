#include "SwapchainKHR.h"

#include <algorithm>

#include "Validation.h"
#include "ComponentList.h"
#include "QueueFamilyHandler.h"
#include "SurfaceKHR.h"
#include "SurfaceKHRSupportOptions.h"


using namespace burst;
using namespace burst::vulkan;

static void clamp(u32& value, u32 min, u32 max) {
	value = std::clamp(value, min, max);
}

static VkSurfaceFormatKHR select_format(const std::vector<VkSurfaceFormatKHR>& formats) {
	for (const auto& format : formats) {
		if (format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR ||
			format.format == VK_FORMAT_B8G8R8A8_SRGB) {
			return format;
		}
	}

	burst::log::warning("Non optimal surface format was picked for swapchain");
	return formats[0];
}

static VkPresentModeKHR select_present_mode(const std::vector<VkPresentModeKHR>& modes) {
	for (const auto& mode : modes) {
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return mode;
		}
	}
	
	burst::log::warning("Non optimal present mode was picked for swapchain");
	return VK_PRESENT_MODE_FIFO_KHR;
}

static VkExtent2D select_swap_extent(
	const VkSurfaceCapabilitiesKHR& capabilities,
	Window& window
) {
	if (capabilities.currentExtent.width != std::numeric_limits<u32>::max()) {
		return capabilities.currentExtent;
	}

	VkExtent2D extent{
		.width = window.framebuffer().width(),
		.height = window.framebuffer().height()
	};

	clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return extent;
}

void burst::vulkan::SwapchainKHRDeleter::operator()(VkSwapchainKHR swapchain) {
	if (nullptr != swapchain) {
		vkDestroySwapchainKHR(device, swapchain, NO_ALLOCATOR);
	}
}

void burst::vulkan::SwapchainKHR::add_dependencies(SetComponentInfo& component_info) {
	component_info.device_extensions.insert(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

SwapchainKHR::Type burst::vulkan::SwapchainKHR::create_component(
	const ComponentCreateInfo& create
) {
	if (nullptr == create.physical_device
		|| nullptr == create.device) {
		throw WaitingForLaterInitialization();
	}

	try {
		auto surface = create.components->get<SurfaceKHR>();
		auto support_options = SurfaceKHRSupportOptions::query(surface, create.physical_device);

		if (!support_options.is_valid()) {
			throw RuntimeError::make("Surface options are not valid for swapchain");
		}

		auto format = select_format(support_options.formats);
		auto present_mode = select_present_mode(support_options.present_modes);
		auto extent = select_swap_extent(support_options.capabilities, *create.window);

		u32 image_count = support_options.capabilities.minImageCount + 1;
		if (image_count > support_options.capabilities.maxImageCount &&
			support_options.capabilities.minImageCount > 0) {
			image_count = support_options.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface;
		create_info.minImageCount = image_count;
		create_info.imageFormat = format.format;
		create_info.imageColorSpace = format.colorSpace;
		create_info.imageExtent = extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		create_info.preTransform = support_options.capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = present_mode;
		create_info.clipped = VK_TRUE;
		create_info.oldSwapchain = nullptr;

		auto graphics = create.queue_family->get_known_family(QueueFamilyType::Graphics);
		auto present = create.queue_family->get_known_family(QueueFamilyType::Present);

		if (!graphics.has_value() || !present.has_value()) {
			throw RuntimeError::make("Graphics and present queue must exist");
		}

		u32 queues[] = {graphics.value(), present.value()};
		if (graphics.value() != present.value()) {
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = queues;
		}
		else {
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			create_info.queueFamilyIndexCount = 0;
			create_info.pQueueFamilyIndices = nullptr;
		}

		VkSwapchainKHR swapchain = nullptr;
		VkResult result = vkCreateSwapchainKHR(create.device, &create_info, NO_ALLOCATOR, &swapchain);
		if (VK_SUCCESS != result) {
			throw RuntimeError::make("Failed to create swapchain, Error: ", result);
		}

		return AutoSwapchainKHR(swapchain, {
			create.device,
			extent,
			format
		});
	}
	catch (const InstanceComponentNotFound&) {
		burst::log::error("No surface component on instance");
		throw;
	}
}
