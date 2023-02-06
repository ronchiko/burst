//#include "RenderContext.h"
//
//constexpr vk::ClearColorValue BLACK =
//	vk::ClearColorValue(std::array<burst::f32, 4>{ 0.f, 0.f, 0.f, 1.f });
//
//namespace burst::vulkan {
//	RenderContext RenderContext::swapchain_context(CommandBuffer& buffer,
//		Pipeline& pipeline,
//		burst::vulkan::Framebuffer& framebuffer)
//	{
//		vk::ClearValue clear_value;
//		clear_value.color = BLACK;
//
//		Vector<vk::ClearValue> clear{ clear_value };
//
//		vk::RenderPassBeginInfo begin_info(pipeline.render_pass(),
//			framebuffer,
//			{ { 0, 0 }, framebuffer.extent() },
//			clear);
//
//		buffer.buffer().beginRenderPass(
//			begin_info, vk::SubpassContents::eInline);
//
//		buffer.buffer().bindPipeline(
//			vk::PipelineBindPoint::eGraphics, pipeline);
//
//		vk::Viewport viewport { 0.f,
//			0.f,
//			static_cast<f32>(framebuffer.extent().width),
//			static_cast<f32>(framebuffer.extent().height),
//			0.f,
//			1.f };
//
//		buffer.buffer().setViewport(0, { viewport });
//
//		buffer.buffer().setScissor(
//			0, { vk::Rect2D({ 0, 0 }, framebuffer.extent()) });
//
//		return RenderContext(buffer);
//	}
//
//	RenderContext::~RenderContext()
//	{
//		m_Buffer.buffer().endRenderPass();
//	}
//}
