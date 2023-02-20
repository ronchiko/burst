#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../Gfx/ImageView.h"

namespace burst::vulkan {
	class Device;
	class RenderPass;

	class Framebuffer
	{
	public:
		/**
		 * Creates a new framebuffer.
		 * 
		 * \param device: The device to create this framebuffer from
		 * \param render_pass: The render pass to bind this framebuffer to
		 * \param source: The source image view for this framebuffer
		 */
		explicit Framebuffer(Device& device, RenderPass& render_pass, const ImageView& source);

		/**
		 * The width of this framebuffer.
		 */
		u32 width() const;

		/**
		 * The height of this framebuffer.
		 */
		u32 height() const;

		/**
		 * Convertor to vk::Framebuffer.
		 */
		explicit operator vk::Framebuffer() const;

	private:
		Uint2 m_Size;
		vk::raii::Framebuffer m_Framebuffer;
	};
}
