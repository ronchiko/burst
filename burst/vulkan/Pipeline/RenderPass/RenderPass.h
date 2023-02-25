#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/Common/Types.h>

#include "../../Configuration.h"
#include "../../Instance/Device/Device.h"
#include "../../Instance/SwapchainKHR/ISwapchainObserver.h"
#include "../../Instance/SwapchainKHR/SwapchainKHR.h"

#include "../../Gfx/ImageView.h"
#include "../../Utils/SwapchainBound.h"
#include "../Framebuffer.h"

#include "Subpass.h"

namespace burst::vulkan {
	class RenderPass final : protected mix::SwapchainBound,
							 public ISwapchainObserver
	{
	public:
		explicit RenderPass(Shared<Configuration> configuration,
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
		void recreate_framebuffers(Device& device);

		/**
		 * Gets a framebuffer object at a given index.
		 *
		 * \param index: The index of the framebuffer
		 */
		const Framebuffer& framebuffer_at(u32 index) const;

		/**
		 * Invoked when a swapchain is resized.
		 *
		 * \param swapchain: The swapchain
		 */
		virtual void on_swapchain_resized(SwapchainKHR& swapchain) override;

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
			Vector<vk::SubpassDependency> dependencies;

			Vector<Unique<IImage>> images;
			Vector<ImageView> views;
			Vector<Framebuffer> framebuffers;
		};

		vk::raii::RenderPass m_RenderPass;
		Subscription m_SwapchainSubscription;
		Data m_Data;
	};
}
