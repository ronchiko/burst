#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../Instance/Gpu/Queues.h"

namespace burst::vulkan {
	class Device;

	class CommandPool
	{
	public:
		/**
		 * Creates a new command pool.
		 * 
		 * \param device: The device to bind this command pool to
		 * \param queue_family_index: The Gpu queue family that this index uses
		 */
		explicit CommandPool(Device& device,
							 u32 queue_family_index);

		/**
		 * Covertor to command pool.
		 */
		explicit operator vk::CommandPool() const;

	private:
		vk::raii::CommandPool m_CommandPool;
	};

}
