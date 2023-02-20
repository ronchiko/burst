#include "RenderPassContext.h"

#include <vulkan/vulkan.hpp>

#include "Commands/CommandBuffer.h"
#include "Instance/SwapchainKHR/SwapchainKHR.h"
#include "RenderPass.h"

namespace burst::vulkan {

	RenderPassContext::RenderPassContext(CommandBuffer& buffer,
										 const RenderPass& pass,
										 u32 framebuffer_index)
		: m_Buffer(buffer)
		, m_ClearValues()
	{
		m_ClearValues.push_back(vk::ClearValue()); // Push black as clear color
		auto& framebuffer = pass.framebuffer_at(framebuffer_index);

		vk::RenderPassBeginInfo begin_info(
			static_cast<vk::RenderPass>(pass),
			static_cast<vk::Framebuffer>(framebuffer),
			VkRect2D{ 0, 0, framebuffer.width(), framebuffer.height() },
			m_ClearValues);

		static_cast<vk::CommandBuffer>(buffer).beginRenderPass(
			begin_info, vk::SubpassContents::eInline);
	}

	RenderPassContext::~RenderPassContext()
	{
		static_cast<vk::CommandBuffer>(m_Buffer).endRenderPass();
	}
}
