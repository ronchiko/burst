#include "DeviceBound.h"

#include "../Instance/Device/Device.h"

namespace burst::vulkan::mix {
	DeviceBound::DeviceBound(Device& device)
		: m_Device(device)
	{}

	const vk::Device DeviceBound::device() const {
		return static_cast<vk::Device>(m_Device);
	}

	vk::raii::Device& DeviceBound::owning_device() {
		return static_cast<vk::raii::Device&>(m_Device);
	}
}
