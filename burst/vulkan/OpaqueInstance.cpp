#include "OpaqueInstance.h"

#include <GLFW/glfw3.h>

#include <burst/Glfw.h>
#include <burst/Common.h>

#include "Validation.h"
#include "PhysicalDevice.h"
#include "DefaultQueueFamilyHandler.h"

using namespace burst;
using namespace burst::vulkan;

constexpr VkApplicationInfo APPLICATION_INFO{
	.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
	.pEngineName = ENGINE_NAME,
	.engineVersion = ENGINE_VERSION,
	.apiVersion = VK_API_VERSION_1_1
};

std::vector<Extension> burst::vulkan::extensions() {
	u32 extensions_count = 0;
	VkResult result = vkEnumerateInstanceExtensionProperties(
		nullptr,
		&extensions_count,
		nullptr
	);

	if (result != VK_SUCCESS) {
		throw RuntimeError::make(
			"Failed to enumeration extensions properties, Error: ", result
		);
	}

	std::vector<VkExtensionProperties> extensions{ extensions_count };
	result = vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, extensions.data());
	if (result != VK_SUCCESS) {
		throw RuntimeError::make(
			"Failed to enumeration extensions properties, Error: ", result
		);
	}

	return burst::convert<VkExtensionProperties, Extension>(
		extensions,
		[](const VkExtensionProperties& ex) {
			return Extension(ex.extensionName, ex.specVersion);
		});
}

/**
 * Throws an exception if not all required extensions are available
 */
void assert_all_required_extensions_available(const std::vector<cstr>& required) 
{
	auto available = burst::vulkan::extensions();

	for (auto& extension : required) {
		if (available.end() == std::find_if(
				available.begin(), 
				available.end(), 
				[&extension](const Extension& ext) {
					return ext.name == extension;
				})) 
		{
			throw RuntimeError::make("Missing required extension: ", extension);
		}
	}
}

VkInstance burst::vulkan::make_instance(
	cstr name, 
	u32 version, 
	const std::vector<cstr>& extensions,
	const std::vector<cstr>& layers
)
{
	assert_all_required_extensions_available(extensions);
	assert_validation_layer_available(layers);

	VkApplicationInfo application_info = APPLICATION_INFO;
	application_info.pApplicationName = name;
	application_info.applicationVersion = version;

	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo = &application_info;
	
	instance_create_info.enabledLayerCount = static_cast<u32>(layers.size());
	instance_create_info.ppEnabledLayerNames = layers.data();

	instance_create_info.enabledExtensionCount = static_cast<u32>(extensions.size());
	instance_create_info.ppEnabledExtensionNames = extensions.data();

	VkInstance instance = nullptr;
	VkResult result = vkCreateInstance(&instance_create_info, nullptr, &instance);
	if (result != VK_SUCCESS) {
		throw RuntimeError::make("Failed to create vulkan instance: ", result);
	}

	return instance;
}

void burst::vulkan::InstanceDeleter::operator()(VkInstance instance)
{
	if (nullptr != instance) {
		vkDestroyInstance(instance, NO_ALLOCATOR);
	}
}
