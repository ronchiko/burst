#include "Errors.h"

static std::string make_component_not_found_message(size_t hash) {
	std::stringstream stream;
	stream << "Instance doesn't have component " << hash;
	return stream.str();
}

static std::string make_component_not_found_message(const std::string& name) {
	std::stringstream stream;
	stream << "Instance doesn't have component " << name;
	return stream.str();
}

burst::vulkan::InstanceComponentNotFound::InstanceComponentNotFound(size_t hash) 
	: RuntimeError(make_component_not_found_message(hash))
{
}

burst::vulkan::InstanceComponentNotFound::InstanceComponentNotFound(const std::string& name)
	: RuntimeError(make_component_not_found_message(name))
{
}

burst::vulkan::WaitingForLaterInitialization::WaitingForLaterInitialization()
	: StaticError("Component is waiting for later initialization")
{}

burst::vulkan::InstanceNotFullyInitialized::InstanceNotFullyInitialized()
	: StaticError("Instance is not fully initialized")
{}