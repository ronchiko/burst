#pragma once

#include <vulkan/vulkan_raii.hpp>

namespace burst::vulkan {
	class Device;


	namespace mix {
		/**
		 * Mixin to add to classes that are bound to a device.
		 */
		class DeviceBound
		{
		public:
			explicit DeviceBound(Device& device);

		protected:
			const vk::Device device() const;

			vk::raii::Device& owning_device();

			Device& m_Device;
		};
	}
}
