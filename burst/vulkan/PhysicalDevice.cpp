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

burst::vulkan::PhysicalDevice::PhysicalDevice(vk::raii::PhysicalDevice device) 
	: m_Device(device)
{
}

const vk::raii::PhysicalDevice& burst::vulkan::PhysicalDevice::device() const {
	return m_Device;
}

void burst::vulkan::PhysicalDevice::find_queue_indecies(
	QueueFamilyHandler& handler,
	std::optional<VkSurfaceKHR> surface
) const
{
	auto queue_families = m_Device.getQueueFamilyProperties();

	u32 i = 0;
	for (const auto& queue_family : queue_families) {
		handler.handle_queue_family(QueueFamilyInfo{
			.index = i,
			.properties = queue_family,
			.physical_device = *m_Device,
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

	VkPhysicalDeviceProperties properties = m_Device.getProperties();
	VkPhysicalDeviceFeatures features = m_Device.getFeatures();

	return rater(properties, features);
}

bool burst::vulkan::PhysicalDevice::check_device_extensions_supported(
	const CStrVector& _required
) const {
	auto available = m_Device.enumerateDeviceExtensionProperties();

	std::set<std::string> required(_required.begin(), _required.end());
	for (const auto& extension : available) {
		required.erase(extension.extensionName);
	}

	return 0 == required.size();
}
