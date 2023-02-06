#pragma once

#include "CommandPool.h"

namespace burst::vulkan {
	class CommandBuffer final
	{
	public:
		/**
		 * Creates a new command buffer.
		 * 
		 * \param device: The device this command is buffer is bound to
		 * \param pool: The pool to create this buffer from
		 */
		explicit CommandBuffer(Device& device, const CommandPool& pool);

	private:
		vk::raii::CommandBuffer m_Buffer;
	};

}
