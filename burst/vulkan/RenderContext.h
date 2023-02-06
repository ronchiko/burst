//#pragma once
//
//#include "CommandBuffer.h"
//#include "Framebuffer.h"
//#include "Pipeline.h"
//#include "SwapchainKHR.h"
//
//namespace burst::vulkan {
//
//	class RenderContext
//	{
//	public:
//		/**
//		 * Creates a new context using a swapchain.
//		 *
//		 * \param buffer: The command buffer of the context
//		 * \param pipeline: The pipeline to render to
//		 * \param swapchain: The swapchain to render to
//		 * \param framebuffer: The framebuffer object
//		 */
//		static RenderContext swapchain_context(CommandBuffer& buffer,
//			Pipeline& pipeline,
//			burst::vulkan::Framebuffer& framebuffer);
//
//		RenderContext(const RenderContext&) = delete;
//		RenderContext& operator=(const RenderContext&) = delete;
//
//		RenderContext(RenderContext&&) = delete;
//		RenderContext& operator=(RenderContext&&) = delete;
//
//		~RenderContext();
//
//	private:
//		RenderContext(CommandBuffer& buffer);
//
//		CommandBuffer& m_Buffer;
//	};
//}
