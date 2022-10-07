#include "Validation.h"

#include <array>

#include <vulkan/vulkan.h>

#include <burst/Common.h>

using namespace burst;

/**
 * Gets the available validation layers
 */
static std::vector<VkLayerProperties> get_available_validation_layers() {
	u32 available_layer_count = 0;
	VkResult result = vkEnumerateInstanceLayerProperties(&available_layer_count, nullptr);
	if (result != VK_SUCCESS) {
		throw RuntimeError::make("Failed to enumerate instance layers: ", result);
	}

	std::vector<VkLayerProperties> available_layers(available_layer_count);
	result = vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers.data());
	if (result != VK_SUCCESS) {
		throw RuntimeError::make("Failed to enumerate instance layers: ", result);
	}

	return available_layers;
}

void burst::vulkan::assert_validation_layer_available(const std::vector<cstr>& required) {
	auto available_layers = get_available_validation_layers();

	for (const auto& layer : required) {
		std::string_view layer_name(layer);

		if (available_layers.end() == std::find_if(
			available_layers.begin(),
			available_layers.end(),
			[&layer_name](const VkLayerProperties& props) {
				return layer_name == props.layerName;
			}
		)) {
			throw RuntimeError::make("Missing validation layer ", layer);
		}
	}
}
