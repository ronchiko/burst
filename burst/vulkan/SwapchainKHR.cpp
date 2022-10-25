#include "SwapchainKHR.h"

#include <algorithm>

#include "Validation.h"
#include "SurfaceKHR.h"
#include "SurfaceKHRSupportOptions.h"


using namespace burst;
using namespace burst::vulkan;

static void clamp(u32& value, u32 min, u32 max) {
	value = std::clamp(value, min, max);
}

static vk::SurfaceFormatKHR select_format(const std::vector<vk::SurfaceFormatKHR>& formats) {
	for (const auto& format : formats) {
		if (format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear ||
			format.format == vk::Format::eB8G8R8A8Srgb) {
			return format;
		}
	}

	burst::log::warning("Non optimal surface format was picked for swapchain");
	return formats[0];
}

static vk::PresentModeKHR select_present_mode(const std::vector<vk::PresentModeKHR >& modes) {
	for (const auto& mode : modes) {
		if (mode == vk::PresentModeKHR::eMailbox) {
			return mode;
		}
	}

	burst::log::warning("Non optimal present mode was picked for swapchain");
	return vk::PresentModeKHR::eFifo;
}

static vk::Extent2D select_swap_extent(
	const VkSurfaceCapabilitiesKHR& capabilities,
	Window& window
) {
	if (capabilities.currentExtent.width != std::numeric_limits<u32>::max()) {
		return capabilities.currentExtent;
	}

	vk::Extent2D extent{
		window.framebuffer().width(),
		window.framebuffer().height()
	};

	clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return extent;
}

namespace burst::vulkan {
	void SwapchainKHR::add_requirements(InstanceRequirements& requirements) const {
		requirements.device_extensions.insert(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	void SwapchainKHR::init(
		const vk::raii::Device& device,
		const Gpu& gpu,
		const AdditionalCreateInfo& info
	) {
		try {
			auto& surface = gpu.get<SurfaceKHR>();
			auto surface_support_options = SurfaceKHRSupportOptions::query(
				*surface.surface(), 
				*gpu.device()
			);

			ASSERT(nullptr != info.window, "Must have a window");

			if (!surface_support_options.is_valid()) {
				throw RuntimeError::make("Surface options are not valid for swapchain");
			}

			auto format = select_format(surface_support_options.formats);
			auto present_mode = select_present_mode(surface_support_options.present_modes);
			auto swap_extent = select_swap_extent(surface_support_options.capabilities, *info.window);
		
			u32 image_count = surface_support_options.capabilities.minImageCount + 1;
			if (image_count > surface_support_options.capabilities.maxImageCount &&
				surface_support_options.capabilities.minImageCount > 0) {
				image_count = surface_support_options.capabilities.maxImageCount;
			}

			u32 queues[] = { 
				gpu.queues()[QueueType::Graphics].value(), 
				gpu.queues()[QueueType::Present].value()
			};
			
			vk::SwapchainCreateInfoKHR swapchain_create_info(
				vk::SwapchainCreateFlagsKHR(),
				*surface.surface(),
				image_count,
				format.format,
				format.colorSpace,
				swap_extent,
				1,
				vk::ImageUsageFlagBits::eColorAttachment,
				vk::SharingMode::eExclusive,
				0,
				queues,
				surface_support_options.capabilities.currentTransform,
				vk::CompositeAlphaFlagBitsKHR::eOpaque,
				present_mode,
				VK_TRUE,
				vk::SwapchainKHR{},
				nullptr
			);

			if (queues[0] != queues[1]) {
				swapchain_create_info.imageSharingMode = vk::SharingMode::eConcurrent;
				swapchain_create_info.queueFamilyIndexCount = 2;
			}

			m_Swapchain = vk::raii::SwapchainKHR(device, swapchain_create_info);
			m_Info.m_Format = format;
			m_Info.m_Extent = swap_extent;

			burst::log::debug("Loaded SwapchainKHR component");
		} 
		catch (const ComponentNotFoundError&) {
			burst::log::error("SurfaceKHR component is required for SwapchainKHR");
			throw MissingRequiredComponentsError("SurfaceKHR component is required for SwapchainKHR component");
		}
	}

	const vk::raii::SwapchainKHR& SwapchainKHR::swapchain() const {
		return m_Swapchain;
	}

	vk::Extent2D& SwapchainKHR::extent() {
		return m_Info.m_Extent;
	}

	vk::SurfaceFormatKHR& SwapchainKHR::format() {
		return m_Info.m_Format;
	}
}
