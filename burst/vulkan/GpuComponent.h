#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "IInstanceDependent.h"

namespace burst::vulkan {

	INTERFACE IGpuComponent : public IInstanceDependent{
	public:
		IFACE_DESTRUCTOR(IGpuComponent);

		IFACE_FUNC(void init(
			const vk::raii::PhysicalDevice&, 
			const AdditionalCreateInfo&
		));
	};

}
