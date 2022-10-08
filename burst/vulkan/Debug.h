#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Window.h>


#include "Component.h"

namespace burst::vulkan {

	struct DebugMessengerDeleter {
		VkInstance instance;

		void operator()(VkDebugUtilsMessengerEXT messenger);
	};

	using AutoDebugMessenger = std::unique_ptr<
		std::remove_pointer_t<VkDebugUtilsMessengerEXT>,
		DebugMessengerDeleter
	>;

	AutoDebugMessenger create_debug_messenger(vk::Instance instance);

	struct DebugMessenger {
		using Type = AutoDebugMessenger;

		static Type create_component(const ComponentCreateInfo&);

		static void add_dependencies(ListComponentInfo<std::set<cstr>>&);
	};
}
