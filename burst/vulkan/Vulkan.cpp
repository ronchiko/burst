#include "burst/Vulkan.h"

// #include "DefaultQueueFamilyHandler.h"
// #include "LogicalDevice.h"
// #include "SwapchainKHR.h"

#include "Instance.h"
#include "Gpu.h"
#include "Device.h"

#include "DefaultGpuAnalyzer.h"
#include "InstanceComponentsList.h"
#ifdef _DEBUG
#include "Debug.h"
#endif
#include "SurfaceKHR.h"


using namespace burst::vulkan;

using Components = InstanceComponentList<
#ifdef _DEBUG
	DebugMessenger,
#endif
	SurfaceKHR
>;


Instance burst::vulkan::load_default_instance(cstr name, u32 version, Window* window) {
	auto components = Components::vector();

	auto instance = make_instance(name, version, components, window);
	
	DefaultGpuAnalyzer analyzer(instance);
	auto gpu = pick_best_gpu(instance, components, analyzer);

	Device device(gpu, components);
	// auto device = make_logical_device<SwapchainKHR>(physical_device);

	return instance;
}