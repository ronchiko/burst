#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "IInstanceDependent.h"

namespace burst::vulkan {
	
	/**
	 * Interface for device components.
	 */
	INTERFACE IDeviceComponent : public IInstanceDependent{
	public:
		IFACE_DESTRUCTOR(IDeviceComponent);

		IFACE_FUNC(void add_requirements(InstanceRequirements&) const);

		IFACE_FUNC(void init(
			const vk::raii::Device&, 
			const AdditionalCreateInfo&
		));
	};


}
