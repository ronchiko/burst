#include "CommandPool.h"

#include "../Instance/Device/Device.h"

namespace burst::vulkan {
	/**
	 * Creates a new command pool.
	 * 
	 * \param device: The device that creates the command pool
	 * \param queue_family_index: The queue index the the pool uses
	 * \return 
	 */
	static vk::raii::CommandPool make_command_pool(Device& device,
												   u32 queue_family_index){
		vk::CommandPoolCreateInfo create_info{
			vk::CommandPoolCreateFlags(), 
			queue_family_index
		};

		return static_cast<vk::raii::Device&>(device).createCommandPool(create_info);
	}

	CommandPool::CommandPool(Device& device, u32 queue_family_index) 
		: m_CommandPool(make_command_pool(device, queue_family_index))
	{}

	CommandPool::operator vk::CommandPool() const {
		return *m_CommandPool;
	}
}
