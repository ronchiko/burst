#include "Debug.h"

#include <burst/Common.h>

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessageHandler(
	VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	VkDebugUtilsMessageTypeFlagsEXT type,
	const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
	void* user_data
) {
	switch (severity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		burst::log::error("Vulkan Warning: ", callback_data->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		burst::log::warning("Vulkan Error: ", callback_data->pMessage);
		break;

	// Mute info & verbose messages
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
	default:
		break;
	}

	return VK_FALSE;
}

namespace burst::vulkan {
	constexpr cstr DEBUG_VALIDATION_LAYER = "VK_LAYER_KHRONOS_validation";

	constexpr VkDebugUtilsMessengerCreateInfoEXT DEBUG_MESSENGER_CREATE_INFO{
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = DebugMessageHandler,
		.pUserData = nullptr
	};

	void DebugMessenger::add_requirements(InstanceRequirements& requirements) const {

		requirements.extensions.insert(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		requirements.validation_layers.insert(DEBUG_VALIDATION_LAYER);
	}

	void DebugMessenger::init(
		const vk::raii::Instance& instance, 
		const AdditionalCreateInfo& info
	) {
		m_Messenger = instance.createDebugUtilsMessengerEXT(DEBUG_MESSENGER_CREATE_INFO);
		burst::log::debug("Debug Messenger loaded");
	}
}
