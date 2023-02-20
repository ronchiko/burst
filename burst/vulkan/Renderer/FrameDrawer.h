#pragma once

#include <functional>

#include "../Sync/Fence.h"
#include "../Sync/Semaphore.h"

#include "../Commands/CommandBuffer.h"

namespace burst::vulkan {
	class Device;
	class SwapchainKHR;
	class RenderPass;

	class FrameDrawer
	{
	public:
		/// The actual drawing implemenation
		using Impl = std::function<void(vk::CommandBuffer, void *)>;

		explicit FrameDrawer(Device& device, CommandPool& pool);
		/**
		 * Draws the frame.
		 */
		void draw(Device& device,
				  SwapchainKHR& swapchain,
				  RenderPass& pass,
				  Impl drawing,
				  void *context);

	private:
		CommandBuffer m_CommandBuffer;

		Fence m_InFlightFence;
		Semaphore m_ImageAvailableSemaphore;
		Semaphore m_RenderFinishedSemaphore;
	};
}
