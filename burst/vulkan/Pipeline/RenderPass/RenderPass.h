#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common.h>

#include "../../Configuration.h"
#include "../../Instance/Device/Device.h"
#include "../../Instance/SwapchainKHR/SwapchainKHR.h"

#include "../../Gfx/ImageView.h"

#include "Subpass.h"

namespace burst::vulkan {
	class RenderPass
	{
	public:
		explicit RenderPass(const Configuration& configuration,
							burst::vulkan::Device& device,
							burst::vulkan::SwapchainKHR& swapchain);


		/**
		 * Convertor to vulkans render pass.
		 */
		explicit operator vk::RenderPass() const;

		/**
		 * Creates the framebuffers for this render pass.
		 *
		 * \param image_views: The image views to create the buffers from
		 * \return A vector for framebuffers
		 */
		Vector<vk::raii::Framebuffer>
		create_framebuffers(Device& device, const Vector<ImageView>& image_views) const;

	private:
		/**
		 * Recreate the render pass.
		 *
		 * \param configuration: The configuration to use
		 * \param swapchain: The swapchain to use
		 * \param device: The device to use
		 */
		void _recreate_render_pass(const Configuration& configuration,
								   SwapchainKHR& swapchain,
								   Device& device);

		struct Data
		{
			Vector<vk::AttachmentDescription> descriptions;
			Vector<Subpass> subpasses;
		};

		vk::raii::RenderPass m_RenderPass;
		Data m_Data;
	};
}
