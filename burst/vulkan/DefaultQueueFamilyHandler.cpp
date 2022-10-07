#include "DefaultQueueFamilyHandler.h"

using namespace burst;
using namespace burst::vulkan;

void burst::vulkan::DefaultQueueFamilyHandler::handle_queue_family(
	const QueueFamilyInfo& info
) {
	if (info.properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
		m_GraphicsFamily = info.index;
		
		if (nullptr != info.physical_device && info.surface.has_value()) {
			VkBool32 present_supported = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(
				info.physical_device,
				info.index,
				info.surface.value(), 
				&present_supported
			);
			if (present_supported) {
				m_PresentFamily = info.index;
			}
		}
	}
}

bool burst::vulkan::DefaultQueueFamilyHandler::is_complete() const {
	return m_GraphicsFamily.has_value() && m_PresentFamily.has_value();
}

std::optional<burst::u32> burst::vulkan::DefaultQueueFamilyHandler::get_known_family(
	QueueFamilyType family
) const {
	switch (family)
	{
	case QueueFamilyType::Graphics:
		return m_GraphicsFamily;
	case QueueFamilyType::Present:
		return m_PresentFamily;
	default:
		return {};
	}
}

std::vector<VkDeviceQueueCreateInfo> 
burst::vulkan::DefaultQueueFamilyHandler::create_queue_creation_infos() const {
	constexpr static float s_QueuePriority = 1.0f;

	std::set<u32> unique_families = {
		m_GraphicsFamily.value(),
		m_PresentFamily.value()
	};
	std::vector<VkDeviceQueueCreateInfo> infos;
	infos.reserve(unique_families.size());

	for (const auto& family : unique_families) {
		VkDeviceQueueCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		create_info.queueCount = 1;
		create_info.queueFamilyIndex = family;
		create_info.pQueuePriorities = &s_QueuePriority;
		
		infos.push_back(create_info);
	}

	return infos;

	
}

