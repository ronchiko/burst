#pragma once

#include "Gpu.h"
#include "IDeviceComponent.h"

namespace burst::vulkan {
	class Device {
	public:
		using IComponent = std::unique_ptr<IDeviceComponent>;
		using Map = IdMap<IComponent>;
		
		/**
		 * Creates a new device.
		 */
		Device(
			Gpu& parent, 
			InstanceComponentVector& components,
			const AdditionalCreateInfo& create_info
		);

		/**
		 * The GPU that this device was created from.
		 */
		const Gpu& gpu() const;

		/**
		 * The vulkan device object.
		 */
		const vk::raii::Device& device() const;

	private:
		Gpu& m_Gpu;
		vk::raii::Device m_Device;
		Map m_Components;
	};
}
