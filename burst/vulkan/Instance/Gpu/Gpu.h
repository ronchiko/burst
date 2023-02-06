#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "IQueueLocator.h"
#include "../SurfaceKHR/SurfaceSupportOptions.h"

namespace burst::vulkan {

	class SurfaceKHR;

	/**
	 * The possible GPU types.
	 */
	enum class GpuType
	{
		Cpu = static_cast<u32>(vk::PhysicalDeviceType::eCpu),
		Integrated = static_cast<u32>(vk::PhysicalDeviceType::eIntegratedGpu),
		Virtual = static_cast<u32>(vk::PhysicalDeviceType::eVirtualGpu),
		Discrete = static_cast<u32>(vk::PhysicalDeviceType::eDiscreteGpu)
	};

	/**
	 * Represents a physical device.
	 */
	class Gpu
	{
	public:
		/**
		 * Creates a new GPU from a physical device.
		 *
		 * \param device: The vulkan physical device object
		 */
		explicit Gpu(vk::raii::PhysicalDevice device);

		/**
		 * The name of the GPU.
		 */
		String name() const;

		/**
		 * The type of the GPU.
		 */
		GpuType type() const;

		/**
		 * Gets all the queue family properties for this GPU.
		 */
		Vector<vk::QueueFamilyProperties> get_queue_family_properties() const;

		/**
		 * Converts to vk::raii::PhysicalDevice.
		 */
		explicit operator vk::raii::PhysicalDevice&();

		/**
		 * Converts to vk::PhysicalDevice.
		 */
		explicit operator vk::PhysicalDevice();

	private:
		friend class GpuSurfaceBinding;

		vk::raii::PhysicalDevice m_Device;
	};
}
