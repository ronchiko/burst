#include "LogicalDevice.h"

#include "Validation.h"
#include "PhysicalDevice.h"

void burst::vulkan::LogicalDeviceDeleter::operator()(VkDevice device) {
	if (nullptr != device) {
		vkDestroyDevice(device, NO_ALLOCATOR);
	}
}

vk::raii::Device burst::vulkan::create_logical_device(
	const vk::raii::PhysicalDevice& physical_device,
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
		static_cast<burst::u32>(component_create_info.lists.device_extensions.size());
	create_info.ppEnabledExtensionNames = component_create_info.lists.device_extensions.data();

	return physical_device.createDevice(create_info);
}

burst::vulkan::LogicalDevice::LogicalDevice(vk::raii::Device device)	
	: m_Device(std::move(device))
{}

burst::vulkan::Queue burst::vulkan::LogicalDevice::get_queue(u32 family_index, u32 queue_index) const {
	vk::raii::Queue vk_queue = m_Device.getQueue(family_index, queue_index);

	return Queue(*vk_queue);
}
