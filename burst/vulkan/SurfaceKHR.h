#pragma once

#include <set>
#include <memory>

#include <vulkan/vulkan_core.h>

#include <burst/Common.h>

#include "Component.h"

namespace burst::vulkan {

	struct SurfaceKHRDeleter {
		VkInstance instance;

		void operator()(VkSurfaceKHR surface);
	};

	using AutoSurfaceKHR = std::unique_ptr<std::remove_pointer_t<VkSurfaceKHR>, vulkan::SurfaceKHRDeleter>;
	
	struct SurfaceKHR {
	public:
		using Type = AutoSurfaceKHR;

		static Type create_component(const ComponentCreateInfo&);

		static void add_dependencies(ListComponentInfo<std::set<cstr>>&);
	};
}
