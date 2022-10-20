#pragma once

#include "Gpu.h"

namespace burst::vulkan {

	class SurfaceKHR;

	/**
	 * The default GPU Analyzer, requires the instance to have a surface
	 * component, can be partially expanded by overriding the 
	 * resolve_queue_family_property
	 */
	class DefaultGpuAnalyzer : public GpuAnalyzer {
	public:
		DefaultGpuAnalyzer(const Instance& instance);

		virtual Score operator()(const Gpu& gpu) override;

	private:
		/**
		 * Given a GPU checks if its qualified to use.
		 */
		bool is_qualified_gpu(const Gpu& gpu, GpuQueues& queues);
	
	protected:
		/**
		 * Resovles a queue family info into the GpuQueues structure.
		 * 
		 * \param gpu: The GPU currently being processed
		 * \param properties: The queue family properties in question
		 * \param surface: The surface component of the instance
		 * \param queues: The GpuQueues structure to populate
		 * \param index: The current queue family index
		 */
		virtual void resolve_queue_family_property(
			const Gpu& gpu,
			const vk::QueueFamilyProperties& properties,
			const SurfaceKHR& surface,
			GpuQueues& queues,
			u32 index
		);

	};
}
