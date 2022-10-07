#include "Debug.h"

#include <burst/Common.h>

static VkDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerCreateInfoEXT& create_info
) {
	auto proc = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
		vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")
	);

	VkDebugUtilsMessengerEXT messenger = nullptr;
	VkResult result = VK_ERROR_EXTENSION_NOT_PRESENT;
	if (nullptr != proc) {
		result = proc(instance, &create_info, nullptr, &messenger);
		if (VK_SUCCESS == result) {
			return messenger;
		}
	}

	throw burst::RuntimeError::make("Failed to create debug messenger: ", result);
}

static void DestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT messenger
) {
	auto proc = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
		vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")
		);

	VkResult result = VK_ERROR_EXTENSION_NOT_PRESENT;
	if (nullptr == proc) {
		throw burst::RuntimeError::make(
			"Failed to destroy debug messenger: ", result
		);
	}

	proc(instance, messenger, nullptr);

}

void burst::vulkan::DebugMessengerDeleter::operator()(
	VkDebugUtilsMessengerEXT messenger
) {
	if (nullptr != messenger) {
		DestroyDebugUtilsMessengerEXT(instance, messenger);
	}
}

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

burst::vulkan::AutoDebugMessenger burst::vulkan::create_debug_messenger(
	VkInstance instance
) {
	VkDebugUtilsMessengerCreateInfoEXT create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	create_info.pfnUserCallback = DebugMessageHandler;
	create_info.pUserData = nullptr;

	VkDebugUtilsMessengerEXT messenger = CreateDebugUtilsMessengerEXT(
		instance,
		create_info
	);
	return AutoDebugMessenger(messenger, DebugMessengerDeleter{ instance });
}

burst::vulkan::DebugMessenger::Type burst::vulkan::DebugMessenger::create_component(
	const ComponentCreateInfo& create_info
) {
	return create_debug_messenger(create_info.instance);
}

void burst::vulkan::DebugMessenger::add_dependencies(
	ListComponentInfo<std::set<cstr>>& lists
) {
	constexpr cstr DEBUG_VALIDATION_LAYER = "VK_LAYER_KHRONOS_validation";

	lists.extensions.insert(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	lists.validation_layers.insert(DEBUG_VALIDATION_LAYER);
}
