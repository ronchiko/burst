#include "CommandBuffer.h"

#include <burst/common/Const.h>

#include "../Instance/Device/Device.h"

namespace burst::vulkan {
	static vk::raii::CommandBuffer make_command_buffer(Device& device,
													   const CommandPool& pool)
	{
		vk::CommandBufferAllocateInfo allocation_info{
			static_cast<vk::CommandPool>(pool),
			vk::CommandBufferLevel::ePrimary,
			/** count = */ 1
		};

		auto buffers = static_cast<vk::raii::Device&>(device).allocateCommandBuffers(
			allocation_info);

		ASSERT(buffers.size() == 1, "Excepted 1 buffer to be create");

		return std::move(buffers.front());
	}

	CommandBuffer::CommandBuffer(Device& device, const CommandPool& pool)
		: m_Buffer(make_command_buffer(device, pool))
	{}
}
