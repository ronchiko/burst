#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "IDeviceComponent.h"

namespace burst::vulkan {

	class SwapchainKHR : public IDeviceComponent {
	public:
		SwapchainKHR() = default;

		IFACE_IMPL(void add_requirements(
			InstanceRequirements&
		) const);

		IFACE_IMPL(void init(
			const vk::raii::Device& device,
			const Gpu& gpu,
			const AdditionalCreateInfo& create_info
		));

		const vk::raii::SwapchainKHR& swapchain() const;

		vk::Extent2D& extent();

		vk::SurfaceFormatKHR& format();

	private:
		struct Info {
			vk::Extent2D m_Extent = {};
			vk::SurfaceFormatKHR m_Format = {};
		} m_Info;

		vk::raii::SwapchainKHR m_Swapchain = nullptr;
	};
}
