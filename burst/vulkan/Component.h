#pragma once

#include <vector>
#include <set>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>
#include <burst/common/Window.h>

#include "QueueFamilyHandler.h"

namespace burst::vulkan {

	class ComponentList;
	class QueueFamilyHandler;

	template<typename T>
	struct ListComponentInfo {
		T extensions;
		T device_extensions;
		T validation_layers;

		template<typename U>
		ListComponentInfo<U> convert() {
			return ListComponentInfo<U> {
				.extensions = U(extensions.begin(), extensions.end()),
				.device_extensions = U(device_extensions.begin(), device_extensions.end()),
				.validation_layers = U(validation_layers.begin(), validation_layers.end())
			};
		}
	};

	using SetComponentInfo = ListComponentInfo<std::set<cstr>>;
	using VectorComponentInfo = ListComponentInfo<const CStrVector>;

	struct ComponentCreateInfo {
		template<typename T>
		using late = std::conditional_t<std::is_pointer_v<T>, 
			T, std::optional<T>>;

		// Always exsiting properties
		VectorComponentInfo lists;
		std::unique_ptr<ComponentList> components;
		std::unique_ptr<QueueFamilyHandler> queue_family;
		vk::raii::Instance instance;
		// Optional properties
		Window* window;
		// Late initialize properties
		late<vk::raii::PhysicalDevice> physical_device;
		late<VkDevice> device;
	};

	/**
	 * Concept for a component (A class that can generate a component
	 */
	template<typename T>
	concept Component = requires(
		ComponentCreateInfo c, 
		ListComponentInfo<std::set<cstr>> s
	) {
		{ T::add_dependencies(s) };
		{ T::create_component(c) } -> std::same_as<typename T::Type>;
		{ typename T::Type(nullptr) };
	};
}
