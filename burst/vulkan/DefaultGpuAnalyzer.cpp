#include "DefaultGpuAnalyzer.h"

#include "SurfaceKHR.h"

namespace burst::vulkan {
	DefaultGpuAnalyzer::DefaultGpuAnalyzer(const Instance& instance) 
		: GpuAnalyzer(instance)
	{}

	GpuAnalyzer::Score DefaultGpuAnalyzer::operator()(const Gpu& gpu) {
		GpuQueues queues;
		auto properties = gpu.device().getProperties();

		if (!is_qualified_gpu(gpu, queues)) {
			return EXCLUDE_GPU;
		}

		u32 score = 0;
		if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
			score += 1000;
		}

		score += properties.limits.maxImageDimension2D;

		return { score, queues };
	}

	bool DefaultGpuAnalyzer::is_qualified_gpu(const Gpu& gpu, GpuQueues& queues) {
		try {
			auto& surface = m_Instance.get<SurfaceKHR>();
			auto queue_family_properties = gpu.device().getQueueFamilyProperties();

			u32 current = 0;
			for (const auto& queue_family_property : queue_family_properties) {
				resolve_queue_family_property(
					gpu,
					queue_family_property,
					surface,
					queues,
					current++
				);
			}

			// Is the queue complete?
			return queues[QueueType::Graphics].has_value()
				&& queues[QueueType::Present].has_value();
		}
		catch (const ComponentNotFoundError&) {
			burst::log::error("Missing SurfaceKHR component from GPU: ", gpu.name());
		}

		return false;
	}

	void DefaultGpuAnalyzer::resolve_queue_family_property(
		const Gpu& gpu,
		const vk::QueueFamilyProperties& properties,
		const SurfaceKHR& surface,
		GpuQueues& queues,
		u32 queue_index
	) {
		if (properties.queueFlags & vk::QueueFlagBits::eGraphics) {
			queues[QueueType::Graphics] = queue_index;

			// Does the surface support KHR
			if (gpu.device().getSurfaceSupportKHR(queue_index, *surface.surface())) {
				queues[QueueType::Present] = queue_index;
			}
		}
	}
}
