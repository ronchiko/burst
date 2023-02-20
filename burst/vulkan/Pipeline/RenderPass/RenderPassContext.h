#pragma once

#include <vulkan/vulkan.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {
	class RenderPass;
	class CommandBuffer;
	class SwapchainKHR;

	class RenderPassContext
	{
	public:
		/**
		 * Starts a new render pass context.
		 */
		explicit RenderPassContext(CommandBuffer& buffer,
								   const RenderPass& render_pass,
								   u32 framebuffer_index);

		~RenderPassContext();

		NOT_COPIABLE(RenderPassContext);
		NOT_MOVABLE(RenderPassContext);

	private:
		CommandBuffer& m_Buffer;
		Vector<vk::ClearValue> m_ClearValues;
	};
}
