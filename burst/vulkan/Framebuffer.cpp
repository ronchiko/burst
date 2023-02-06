//#include "Framebuffer.h"
//
//#include "SwapchainKHR.h"
//
//namespace burst::vulkan {
//
//	Framebuffer::Framebuffer(nullptr_t)
//		: m_Framebuffer(nullptr)
//	{}
//
//	Framebuffer::Framebuffer(
//		vk::raii::Framebuffer framebuffer, vk::Extent2D extent)
//		: m_Framebuffer(std::move(framebuffer))
//		, m_Extent(extent)
//	{}
//
//	std::vector<Framebuffer> Framebuffer::create(
//		const Device& device, const Pipeline& pipeline)
//	{
//		const SwapchainKHR& swapchain = device.get<SwapchainKHR>();
//
//		auto images = swapchain.image_views();
//		std::vector<Framebuffer> buffers;
//		buffers.reserve(images.size());
//
//		for(const auto& image : images) {
//			std::vector<vk::ImageView> attachments{ *image };
//
//			vk::FramebufferCreateInfo create_info(vk::FramebufferCreateFlags(),
//				pipeline.render_pass(),
//				attachments,
//				swapchain.extent().width,
//				swapchain.extent().height,
//				1);
//
//			buffers.push_back(
//				Framebuffer(vk::raii::Framebuffer(device.device(), create_info),
//					swapchain.extent()));
//		}
//
//		return buffers;
//	}
//
//	Framebuffer::operator vk::Framebuffer() const
//	{
//		return *m_Framebuffer;
//	}
//
//	vk::Extent2D Framebuffer::extent() const
//	{
//		return m_Extent;
//	}
//
//	Framebuffers::Framebuffers(Device& device, const Pipeline& pipeline)
//		: m_Swapchain(device.get<SwapchainKHR>())
//		, m_Framebuffers(Framebuffer::create(device, pipeline))
//	{}
//
//	Framebuffer& Framebuffers::operator[](u32 index)
//	{
//		if(index >= m_Framebuffers.size()) {
//			throw RuntimeError::make("Attempted to access frambuffer ",
//				index + 1,
//				" when only ",
//				m_Framebuffers.size(),
//				"Are available");
//		}
//
//		return m_Framebuffers[index];
//	}
//
//	vk::Extent2D Framebuffers::extent() const
//	{
//		return m_Swapchain.extent();
//	}
//}