#include "PhysicalDevice.h"

#include "Validation.h"

using namespace burst;

burst::u32 burst::vulkan::default_physical_device_rater(
	const VkPhysicalDeviceProperties& properties,
	const VkPhysicalDeviceFeatures& features
) {
	u32 score = 0;
	if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
	}

	score += properties.limits.maxImageDimension2D;
	return score;
}

burst::vulkan::DeviceNotFoundError::DeviceNotFoundError(burst::cstr message)
	: StaticError(message)
{}

burst::vulkan::PhysicalDevice::PhysicalDevice(VkPhysicalDevice device) 
	: m_Device(device)
{
}

VkPhysicalDevice burst::vulkan::PhysicalDevice::device() const {
	return m_Device;
}

void burst::vulkan::PhysicalDevice::find_queue_indecies(
	QueueFamilyHandler& handler,
	std::optional<VkSurfaceKHR> surface
) const
{
	u32 queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_Device, &queue_family_count, nullptr);

	std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(m_Device, &queue_family_count, queue_families.data());

	u32 i = 0;
	for (const auto& queue_family : queue_families) {
		handler.handle_queue_family(QueueFamilyInfo{
			.index = i,
			.properties = queue_family,
			.physical_device = m_Device,
			.surface = surface
		});

		if (handler.is_complete()) {
			break;
		}
	}
}


u32 burst::vulkan::PhysicalDevice::rate(
	const CStrVector& device_extensions,
	burst::vulkan::QueueFamilyHandler& queue_family_handler,
	burst::vulkan::PhysicalDevice::Rater rater
) {
	find_queue_indecies(queue_family_handler);
	if (!queue_family_handler.is_complete()) {
		return SCORE_EXCLUDE_DEVICE;
	}

	if (!check_device_extensions_supported(device_extensions)) {
		return SCORE_EXCLUDE_DEVICE;
	}

	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;

	vkGetPhysicalDeviceProperties(m_Device, &properties);
	vkGetPhysicalDeviceFeatures(m_Device, &features);

	return rater(properties, features);
}

std::vector<VkPhysicalDevice> burst::vulkan::PhysicalDevice::query_devices(
	VkInstance instance
) {
	u32 device_count = 0;
	vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

	if (device_count == 0) {
		throw burst::vulkan::DeviceNotFoundError(
			"Failed to find any supported GPUs."
		);
	}

	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

	return devices;
}

std::vector<VkExtensionProperties> burst::vulkan::PhysicalDevice::get_available_extensions() const {
	u32 count = 0;
	vkEnumerateDeviceExtensionProperties(m_Device, nullptr, &count, nullptr);

	std::vector<VkExtensionProperties> available_extensions(count);
	vkEnumerateDeviceExtensionProperties(m_Device, nullptr, &count, available_extensions.data());

	return available_extensions;
}

bool burst::vulkan::PhysicalDevice::check_device_extensions_supported(
	const CStrVector& _required
) const {
	auto available = get_available_extensions();

	std::set<std::string> required(_required.begin(), _required.end());
	for (const auto& extension : available) {
		required.erase(extension.extensionName);
	}

	return 0 == required.size();
}
