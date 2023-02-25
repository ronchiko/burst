#include "DebugMessenger.h"

#include <burst/common/Log.h>

#include "Instance.h"

// Message handler for vulkan
VKAPI_ATTR VkBool32 VKAPI_CALL
DebugMessageHandler(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
					VkDebugUtilsMessageTypeFlagsEXT type,
					const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
					void *user_data)
{
	switch(severity) {
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		burst::log::error("Vulkan Warning: ", callback_data->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		burst::log::warning("Vulkan Error: ", callback_data->pMessage);
		break;

	// Mute info & verbose messages
#ifdef VEBOSE
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		burst::log::debug("Vulkan Message: ", callback_data->pMessage);
		break;

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		burst::log::info("Vulkan Message: ", callback_data->pMessage);
		break;
#endif
	default:
		break;
	}

	return VK_FALSE;
}

namespace burst::vulkan {
	/**
	 * Creates the Debug messenger.
	 */
	static vk::raii::DebugUtilsMessengerEXT create_messenger(Instance& instance)
	{
		vk::DebugUtilsMessengerCreateInfoEXT info(
			vk::DebugUtilsMessengerCreateFlagsEXT(0),
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
				vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
				vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			&DebugMessageHandler);

		return static_cast<vk::raii::Instance&>(instance)
			.createDebugUtilsMessengerEXT(info);
	}

	DebugMessenger::DebugMessenger(Instance& instance)
		: m_Messenger(create_messenger(instance))
	{}

}
