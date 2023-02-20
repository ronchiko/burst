#include "FrameDrawer.h"

#include "Commands/CommandPool.h"
#include "Commands/CommandRecorder.h"
#include "Instance/Device/Device.h"
#include "Instance/SwapchainKHR/SwapchainKHR.h"
#include "Pipeline/RenderPass/RenderPass.h"
#include "Pipeline/RenderPass/RenderPassContext.h"

namespace burst::vulkan {
	FrameDrawer::FrameDrawer(Device& device, CommandPool& pool)
		: m_CommandBuffer(device, pool)
		, m_InFlightFence(device)
		, m_ImageAvailableSemaphore(device)
		, m_RenderFinishedSemaphore(device)
	{}

	void FrameDrawer::draw(Device& device,
						   SwapchainKHR& swapchain,
						   RenderPass& render_pass,
						   Impl draw,
						   void *context)
	{
		m_InFlightFence.wait();

		u32 next_image = swapchain.acquire_next_image(m_ImageAvailableSemaphore);


		m_InFlightFence.reset();
		{
			// Render
			CommandRecorder recorder(m_CommandBuffer);
			RenderPassContext pass_context(m_CommandBuffer, render_pass, next_image);

			draw(static_cast<vk::CommandBuffer>(m_CommandBuffer), context);
		}

		auto queue = device.get_queue(0); // TODO: Make some queue provider class
		queue.push_stage(m_ImageAvailableSemaphore,
						 vk::PipelineStageFlagBits::eColorAttachmentOutput);
		queue.sumbit(m_CommandBuffer, m_RenderFinishedSemaphore, m_InFlightFence);

		queue.present(m_RenderFinishedSemaphore, swapchain, next_image);
	}
}
