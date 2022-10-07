#include "burst/Vulkan.h"

#include "DefaultQueueFamilyHandler.h"
#include "LogicalDevice.h"
#include "SurfaceKHR.h"
#include "SwapchainKHR.h"
#include "OpaqueInstance.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

using namespace burst::vulkan;
 
using DefaultInstance = OpaqueInstance<
#ifdef _DEBUG
	DebugMessenger,
#endif
	SurfaceKHR,
	SwapchainKHR
>;


struct burst::vulkan::_Instance {
	DefaultInstance instance;
};

Instance burst::vulkan::load_default_instance(cstr name, u32 version, Window* window) {
	auto opaque_instance = DefaultInstance::make<DefaultQueueFamilyHandler>(name, version, window);
	
	return Instance(new _Instance{ std::move(opaque_instance) });
}