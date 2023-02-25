#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../../Configuration.h"

#include "Queue.h"

namespace burst::vulkan {

	class Gpu;

	/**
	 * A vulkan logical device.
	 */
	class Device
	{
	public:
		Device() = default;

		/**
		 * Create a new device.
		 *
		 * \param gpu: The gpu the device is bound to
		 * \param queues: The gpu queues of the gpu
		 * \param configuration: The configuration for the device
		 */
		explicit Device(Gpu& gpu,
						Queues& queues,
						Shared<Configuration> configuration);

		/**
		 * Convertor to vk::raii::Device.
		 */
		explicit operator vk::raii::Device &();

		/**
		 * Convertor to vk::Device.
		 */
		explicit operator vk::Device() const;

		/**
		 * Gets a queue from this device.
		 * 
		 * \param family_index: The family index of this queue (get from the Queues object)
		 * \param index: The index of the queue inside that family
		 */
		Queue get_queue(u32 family_index, u32 index = 0) const;

	private:
		vk::raii::Device m_Device = nullptr;
		bool m_IsRendering = false;
	};

}
