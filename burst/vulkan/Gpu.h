#pragma once

#include <unordered_map>
#include <optional>

#include <vulkan/vulkan_raii.hpp>

#include "Instance.h"
#include "Queues.h"
#include "GpuComponent.h"

namespace burst::vulkan {

	/**
	 * Represnts a GPU that can be used.
	 */
	class Gpu {
	public:
		using IComponent = std::unique_ptr<IGpuComponent>;
		using Map = std::unordered_map<u32, IComponent>;

		Gpu(
			vk::raii::PhysicalDevice device, 
			Instance& parent,
			Map compoennts,
			GpuQueues queues
		);

		/**
		 * The instance that the physical device was created from.
		 */
		const Instance& instance() const;

		/**
		 * The vulkan physical device.
		 */
		const vk::raii::PhysicalDevice& device() const;

		/**
		 * Gets the name of the device.
		 */
		std::string name() const;

		/**
		 * Gets the limits of the GPU.
		 */
		vk::PhysicalDeviceLimits limits() const;

		/**
		 * The type of the GPU.
		 */
		vk::PhysicalDeviceType type() const;

		/**
		 * The Gpu Queues.
		 */
		const GpuQueues& queues() const;

	private:
		Instance& m_Parent;
		vk::raii::PhysicalDevice m_Device;
		Map m_Components;
		GpuQueues m_Queues;
	};

	/**
	 * Class for rating GPUs compatibility with an instance
	 */
	class GpuAnalyzer {
	public:
		/**
		 * The score provided by an analyzer about a GPU.
		 */
		struct Score {
			u32 score;
			GpuQueues queues;
		};

		static constexpr u32 SCORE_EXCLUDE = 0;
		static constexpr Score EXCLUDE_GPU = { SCORE_EXCLUDE, {} };

		GpuAnalyzer(const Instance& instance);

		/**
		 * The rating method, should provide a score for the GPU (higher is better)
		 * and acquire the required GPU queues by proceeding processes.
		 * 
		 * \param gpu: The gpu to analyze
		 */
		virtual Score operator()(const Gpu& gpu) = 0;

	protected:
		const Instance& m_Instance;
	};

	/**
	 * From all avialable GPUs picks the most suitable one according to the rater.
	 * 
	 * \param instance: The instance to pick the GPU from
	 * \param rater: The rater for the GPUs
	 */
	Gpu pick_best_gpu(
		Instance& instance,
		InstanceComponentVector& components,
		GpuAnalyzer& rater
	);
}
