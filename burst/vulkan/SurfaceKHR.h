#pragma once

#include <set>
#include <memory>

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "InstanceComponent.h"

namespace burst::vulkan {

	class SurfaceKHR : public IInstanceComponent {
	public:
		SurfaceKHR();

		IFACE_IMPL(void add_requirements(
			InstanceRequirements& requirements
		) const);

		IFACE_IMPL(void init(
			const vk::raii::Instance&,
			const AdditionalCreateInfo& create_info
		));

		const vk::raii::SurfaceKHR& surface() const;

	private:
		vk::raii::SurfaceKHR m_Surface;
	};
}
