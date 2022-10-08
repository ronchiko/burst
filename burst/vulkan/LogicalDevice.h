#pragma once

#include <set>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>

#include "Queue.h"
#include "PhysicalDevice.h"
#include "QueueFamilyHandler.h"
#include "Component.h"

namespace burst::vulkan {

	vk::raii::Device create_logical_device(
		const vk::raii::PhysicalDevice& physical_device,
		const ComponentCreateInfo& create_info
	);

	class LogicalDevice final {
	public:
		LogicalDevice() = default;
		explicit LogicalDevice(vk::raii::Device device);

		/**
		 * Gets a queue from the device
		 */
		Queue get_queue(u32 family_index, u32 queue_index = 0) const;


		const vk::raii::Device& device() const;

	private:
		vk::raii::Device m_Device = nullptr;
	};
}
