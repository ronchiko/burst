#pragma once

#include <Burst/Common/IRenderer.h>

#include "../Configuration.h"

#include "../Instance/Gpu/Gpu.h"
#include "../Instance/Instance.h"

#include "../Errors.h"

namespace burst::vulkan {

	/**
	 * Finds the most suitable gpu out of all the ones available to the
	 * instace.
	 * 
	 * \param instance: The instance to search in
	 * \param
	 * config: The configuration
	 * \return: The most fitting gpu found
	 */
	static Gpu find_suitable_gpu(Instance& instance, const Configuration& config)
	{
		const auto& available_gpus = instance.gpus();

		ASSERT(available_gpus.size(), "Didn't find any gpu's");
		ASSERT(nullptr != config.gpu.analyzer, "No gpu analyzer in config");

		// Foreach gpu rate it using the configurations GPU analyzer
		// And if its a suitable gpu add it to the rating
		Multimap<u32, Gpu> gpu_ratings;
		for(const auto& gpu : available_gpus) {
			const auto score = config.gpu.analyzer->rate(gpu);

			// Check if gpu is rejected
			if(score <= IGpuAnalyzer::REJECT_GPU) {
				continue;
			}

			gpu_ratings.insert({ score, gpu });
		}

		// Get the first elements gpu, or raise an error
		if(!gpu_ratings.empty()) {
			return gpu_ratings.begin()->second;
		}

		throw NoSuitableGpuError();
	}

	/**
	 * Creates a gpu queues object for a given gpu.
	 *
	 * \param gpu: The gpu to create the object for
	 * \param config: The configuration to use
	 * \param surface[optional]: The surface to use
	 * 
	 * \return: The gpu queues object
	 */
	static Queues create_gpu_queues_object(const Gpu& gpu,
										   const Configuration& config,
										   Optional<SurfaceKHR>& surface)
	{
		Queues queues;

		// For each queue family property call each one of the locators registered
		// in the configuration.
		for(const auto& [index, property] :
			index(gpu.get_queue_family_properties())) {
			QueueFamilyProperties properties(
				property, index, gpu, GET_ADDRESS(surface));

			for(const auto& locator : config.gpu.locators) {
				locator->locate(properties, queues);
			}
		}

		return queues;
	}
}
