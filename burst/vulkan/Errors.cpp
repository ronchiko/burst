#include "Errors.h"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>

static std::string make_component_not_found_message(size_t hash)
{
	std::stringstream stream;
	stream << "Instance doesn't have component " << hash;
	return stream.str();
}

static std::string make_component_not_found_message(const std::string& name)
{
	std::stringstream stream;
	stream << "Instance doesn't have component " << name;
	return stream.str();
}

burst::vulkan::InstanceComponentNotFound::InstanceComponentNotFound(size_t hash)
	: RuntimeError(make_component_not_found_message(hash))
{}

burst::vulkan::InstanceComponentNotFound::InstanceComponentNotFound(
	const std::string& name)
	: RuntimeError(make_component_not_found_message(name))
{}

burst::vulkan::MissingRequiredComponentsError::MissingRequiredComponentsError()
	: MissingRequiredComponentsError("Missing one or more required components")
{}

burst::vulkan::MissingRequiredComponentsError::MissingRequiredComponentsError(
	cstr message)
	: StaticError(message)
{}

burst::vulkan::MissingRequiredLayersError::MissingRequiredLayersError()
	: StaticError("Missing one or more required layers")
{}

burst::vulkan::NoSuitableGpuError::NoSuitableGpuError()
	: StaticError("No suitable GPU found")
{}

burst::vulkan::ComponentNotFoundError::ComponentNotFoundError(const cstr name)
	: RuntimeError(concat("Didn't find component ", name))
{}

burst::vulkan::MissingRequiredQueueError::MissingRequiredQueueError()
	: StaticError("Missing required queue")
{}

burst::vulkan::VulkanError::VulkanError(
	const std::string& message, vk::Result result)
	: RuntimeError(
		  concat(message, ": ", string_VkResult(static_cast<VkResult>(result))))
{}

burst::vulkan::VulkanError::VulkanError(
	const std::string& message, VkResult result)
	: RuntimeError(
		  concat(message, ": ", string_VkResult(result)))
{}

burst::vulkan::FailedToCreateCommandPoolError::FailedToCreateCommandPoolError(cstr msg)
	: StaticError(msg)
{}
