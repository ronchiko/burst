#pragma once

#include <vulkan/vulkan_raii.hpp>

namespace burst::vulkan {
	class Instance;

	/**
	 * Vulkans debug messenger.
	 */
	class DebugMessenger
	{
	public:
		DebugMessenger() = default;

		explicit DebugMessenger(Instance& instance);

	private:
		vk::raii::DebugUtilsMessengerEXT m_Messenger = nullptr;
	};
}
