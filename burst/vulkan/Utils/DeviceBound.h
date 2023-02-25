#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Types.h>

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

			const vk::Device device() const;

			vk::raii::Device& owning_device();

			Ref<Device> burst_device();

		protected:
			Device& m_Device;
		};
	}
}
