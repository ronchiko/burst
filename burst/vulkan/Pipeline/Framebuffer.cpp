#include "Framebuffer.h"

#include "../Instance/Device/Device.h"
#include "RenderPass/RenderPass.h"

namespace burst::vulkan {
	Framebuffer::Framebuffer(Device& device, RenderPass& render_pass, const ImageView& view)
		: m_Size(view.dimensions().width(), view.dimensions().height())
		, m_Framebuffer(nullptr)
	{
		Array<vk::ImageView, 1> vk_view{ static_cast<vk::ImageView>(view) };

		m_Framebuffer = static_cast<vk::raii::Device&>(device).createFramebuffer(
			vk::FramebufferCreateInfo{
				vk::FramebufferCreateFlags(),
				static_cast<vk::RenderPass>(render_pass),
				vk_view,
				view.dimensions().width(),
				view.dimensions().height(),
				1,
			});
	}

	u32 Framebuffer::width() const {
		return m_Size.x;
	}

	u32 Framebuffer::height() const {
		return m_Size.y;
	}

	Framebuffer::operator vk::Framebuffer() const {
		return *m_Framebuffer;
	}
}
