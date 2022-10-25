#include "burst/Vulkan.h"

// #include "DefaultQueueFamilyHandler.h"
// #include "LogicalDevice.h"
// #include "SwapchainKHR.h"

#include <vulkan/vulkan.hpp>

#include "Instance.h"
#include "Gpu.h"
#include "Device.h"

#include "DefaultGpuAnalyzer.h"
#include "InstanceComponentsList.h"
#ifdef _DEBUG
#include "Debug.h"
#endif
#include "SurfaceKHR.h"
#include "SwapchainKHR.h"


using namespace burst::vulkan;

using Components = InstanceComponentList<
	SwapchainKHR,
	SurfaceKHR
#ifdef _DEBUG
	, DebugMessenger
#endif
>;

struct VulkanState {
	Instance instance;
	Gpu gpu;
	// Device device;
};

static void log_non_ideal_gpu_selection(const Gpu& gpu) {
	switch (gpu.type())
	{
	case vk::PhysicalDeviceType::eIntegratedGpu:
		burst::log::warning("Selected integrated GPU");
		break;
	default:
		break;
	}
}

burst::AbstractPointer burst::vulkan::load_default_instance(cstr name, u32 version, Window* window) {
	auto components = Components::vector();

	auto [instance, info] = make_instance(name, version, components, window);

	DefaultGpuAnalyzer analyzer(instance);
	auto gpu = pick_best_gpu(instance, components, analyzer, info);
	log_non_ideal_gpu_selection(gpu);
	
	Device device(gpu, components, info);

	return burst::abstract(new VulkanState{
			std::move(instance),
			std::move(gpu)
			// std::move(device)
		});
}