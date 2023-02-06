#include "RenderPass.h"

#include <burst/common/Meta.h>

using namespace vk;

namespace burst::vulkan {

	RenderPass::RenderPass(const Configuration& configuration,
						   Device& device,
						   SwapchainKHR& swapchain)
		: m_RenderPass(nullptr)
		, m_Data{}
	{
		_recreate_render_pass(configuration, swapchain, device);
	}

	RenderPass::operator vk::RenderPass() const
	{
		return *m_RenderPass;
	}

	Vector<vk::raii::Framebuffer>
	RenderPass::create_framebuffers(Device& device, const Vector<ImageView>& views) const
	{
		return convert<vk::raii::Framebuffer, ImageView>(
			views, [this, &device](const ImageView& view) {
				Array<vk::ImageView, 1> image_views{ static_cast<vk::ImageView>(
					view) };
				const auto& dimensions = view.dimensions();

				return static_cast<vk::raii::Device&>(device).createFramebuffer(
					vk::FramebufferCreateInfo{
						vk::FramebufferCreateFlags(),
						*m_RenderPass,
						image_views,
						dimensions.width(),
						dimensions.height(),
						1,
					});
			});
	}

	void RenderPass::_recreate_render_pass(const Configuration& configuration,
										   SwapchainKHR& swapchain,
										   Device& device)
	{
		m_Data.descriptions.clear();
		m_Data.subpasses.clear();

		m_Data.descriptions.reserve(configuration.pipeline.color_attachments.size());
		m_Data.subpasses.reserve(configuration.pipeline.color_attachments.size());

		// TODO: prober construction of the pipeline

		// Create all of the attachment
		for(const auto& [index, color_attachment] :
			index(configuration.pipeline.color_attachments)) {
			m_Data.descriptions.push_back(AttachmentDescription{
				/** flags = */ AttachmentDescriptionFlags(),
				/** format = */ swapchain.format().format,
				/** samples = */ SampleCountFlagBits::e1,
				/** load_operation = */ AttachmentLoadOp::eClear,
				/** store_operation = */ AttachmentStoreOp::eStore,
				/** stencil_load_op = */ AttachmentLoadOp::eDontCare,
				/** stencil_store_op = */ AttachmentStoreOp::eDontCare,
				/** initial_layout = */ ImageLayout::eUndefined,
				/** final_layout = */ ImageLayout::ePresentSrcKHR,
			});
		}

		m_Data.subpasses.push_back(Subpass{
			Subpass::Type::Graphics,
			Vector<AttachmentReference>(),
			Vector<AttachmentReference>({
				AttachmentReference(0, ImageLayout::eColorAttachmentOptimal),
			}),
		});


		auto subpasses = vec_cast<SubpassDescription>(m_Data.subpasses);
		RenderPassCreateInfo create_info{
			RenderPassCreateFlags(),
			m_Data.descriptions,
			subpasses,
		};

		m_RenderPass =
			raii::RenderPass(static_cast<raii::Device&>(device), create_info);
	}
}
