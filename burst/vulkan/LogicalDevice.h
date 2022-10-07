#pragma once

#include <set>

#include <vulkan/vulkan.h>

#include "Queue.h"
#include "PhysicalDevice.h"
#include "QueueFamilyHandler.h"
#include "Component.h"

namespace burst::vulkan {

	struct LogicalDeviceDeleter {
		void operator()(VkDevice);
	};

	using AutoLogicalDevice = std::unique_ptr<
		std::remove_pointer_t<VkDevice>,
		LogicalDeviceDeleter
	>;

	VkDevice create_logical_device(
		burst::vulkan::PhysicalDevice& physical_device,
		const ComponentCreateInfo& create_info
	);

	class LogicalDevice final {
	public:
		LogicalDevice(VkDevice device);

		/**
		 * Gets a queue from the device
		 */
		Queue get_queue(u32 family_index, u32 queue_index = 0) const;

	private:
		AutoLogicalDevice m_Device = nullptr;
	};
}
