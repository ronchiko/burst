#include "LogicalDevice.h"

#include "Validation.h"
#include "PhysicalDevice.h"

void burst::vulkan::LogicalDeviceDeleter::operator()(VkDevice device) {
	if (nullptr != device) {
		vkDestroyDevice(device, NO_ALLOCATOR);
	}
}

VkDevice burst::vulkan::create_logical_device(
	burst::vulkan::PhysicalDevice& physical_device,
	const ComponentCreateInfo& component_create_info
) {
	auto queues = component_create_info.queue_family->create_queue_creation_infos();

	VkDeviceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	VkPhysicalDeviceFeatures device_features{};
	create_info.queueCreateInfoCount = queues.size();
	create_info.pQueueCreateInfos = queues.data();
	create_info.pEnabledFeatures = &device_features;

	create_info.enabledLayerCount = 
		static_cast<burst::u32>(component_create_info.lists.validation_layers.size());
	create_info.ppEnabledLayerNames = component_create_info.lists.validation_layers.data();
	create_info.enabledExtensionCount = 
		static_cast<u32>(component_create_info.lists.device_extensions.size());
	create_info.ppEnabledExtensionNames = component_create_info.lists.device_extensions.data();

	VkDevice device = nullptr;
	VkResult device_creation_result = vkCreateDevice(
		physical_device.device(), 
		&create_info, 
		burst::vulkan::NO_ALLOCATOR, 
		&device
	);

	if (device_creation_result != VK_SUCCESS) {
		throw burst::RuntimeError::make("Failed to create vulkan logical device, Error:", device_creation_result);
	}

	return device;
}

burst::vulkan::LogicalDevice::LogicalDevice(VkDevice device)	
	: m_Device(device)
{}

burst::vulkan::Queue burst::vulkan::LogicalDevice::get_queue(u32 family_index, u32 queue_index) const {
	VkQueue vk_queue = nullptr;
	vkGetDeviceQueue(m_Device.get(), family_index, queue_index, &vk_queue);

	if (nullptr == vk_queue) {
		throw burst::RuntimeError::make("No queue with family: ", family_index, ", queue: ", queue_index);
	}

	return Queue(vk_queue);
}
