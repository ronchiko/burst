#include "Extensions.h"

#include <vulkan/vulkan.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {

	/**
	 * Cached getter for getting all the available extensions.
	 */
	static Set<String>& get_all_avialable_extensions()
	{
		static Set<String> s_Extensions{};

		if(s_Extensions.size() > 0) {
			return s_Extensions;
		}

		return s_Extensions = burst::convert<Set<String>>(
				   vk::enumerateInstanceExtensionProperties(),
				   [](const auto& e) { return e.extensionName; });
	}

	/**
	 * Gets all the available layers for vulkan (Cached).
	 */
	static Set<String>& get_all_available_layers()
	{
		static Set<String> s_Layers{};

		if(s_Layers.size() > 0) {
			return s_Layers;
		}

		return s_Layers = burst::convert<Set<String>>(
				   vk::enumerateInstanceLayerProperties(),
				   [](const auto& l) { return l.layerName; });
	}

	/**
	 * Checks if an instance extension is support by vulkan.
	 *
	 * \param ext: The name of the extension
	 * \return True if the extension is supported
	 */
	static bool is_instance_extensions_supported(const String& ext)
	{
		auto& exts = get_all_avialable_extensions();

		return exts.find(ext) != exts.end();
	}

	/**
	 * Checks if an instance layer is support by vulkan.
	 *
	 * \param layer: The name of the layer
	 * \return True if the layer is supported
	 */
	static bool is_instance_layer_supported(const String& layer)
	{
		auto& layers = get_all_available_layers();

		return layers.find(layer) != layers.end();
	}

	bool is_requirement_supported(Requirement requirement)
	{
		switch(requirement.type) {
		case RequirementType::InstanceExtension:
			return is_instance_extensions_supported(requirement.value);
		case RequirementType::ValidationLayer:
			return is_instance_layer_supported(requirement.value);
		default:
			return false;
		}
	}

	Set<String> all_layers()
	{
		return get_all_available_layers();
	}

	Set<String> all_extensions()
	{
		return get_all_avialable_extensions();
	}
}
