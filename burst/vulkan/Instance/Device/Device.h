#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../../Configuration.h"

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
		 * \param configuration: The configuration for the device
		 */
		explicit Device(Gpu& gpu,
						Queues& queues,
						const Configuration& configuration);

		/**
		 * Checks if this device can be used for rendering.
		 * 
		 * \return: True is the device is capable of rendering
		 */
		constexpr bool is_rendering() const {
			return m_IsRendering;
		}

		/**
		 * Convertor to vk::raii::Device.
		 */
		explicit operator vk::raii::Device &();

		/**
		 * Convertor to vk::Device.
		 */
		explicit operator vk::Device() const;

	private:
		vk::raii::Device m_Device = nullptr;
		bool m_IsRendering = false;
	};

}
