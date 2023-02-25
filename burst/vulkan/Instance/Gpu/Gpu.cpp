#include "Gpu.h"

#include <burst/Common.h>

#include "../SurfaceKHR/SurfaceKHR.h"

namespace burst::vulkan {

	Gpu::Gpu(vk::raii::PhysicalDevice device)
		: m_Device(std::move(device))
	{}

	String Gpu::name() const
	{
		return m_Device.getProperties().deviceName;
	}

	GpuType Gpu::type() const
	{
		return static_cast<GpuType>(m_Device.getProperties().deviceType);
	}

	Vector<vk::QueueFamilyProperties> Gpu::get_queue_family_properties() const
	{
		return m_Device.getQueueFamilyProperties();
	}

	Gpu::operator vk::raii::PhysicalDevice& () {
		return m_Device;
	}

	Gpu::operator vk::PhysicalDevice() const {
		return *m_Device;
	}
}
