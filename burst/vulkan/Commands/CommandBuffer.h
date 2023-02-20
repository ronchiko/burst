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

		/**
		 * Starts recording this command buffer.
		 * 
		 * \param reset: Should reset the buffer as well
		 * 
		 * \returns: True if it was successful
		 */
		bool start_recording(bool reset = true);

		/**
		 * Stops recording into this buffer.
		 */
		bool stop_recording();

		/**
		 * Convertor to vk::CommandBuffer.
		 */
		operator VkCommandBuffer() const;

	private:
		vk::raii::CommandBuffer m_Buffer;
	};

}
