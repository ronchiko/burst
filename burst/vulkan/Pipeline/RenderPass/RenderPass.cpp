#include "RenderPass.h"

#include <burst/common/Meta.h>
#include <burst/common/Types/Iterators/Functions.h>

using namespace vk;

namespace burst::vulkan {

	RenderPass::RenderPass(Shared<Configuration> configuration,
						   Device& device,
						   SwapchainKHR& swapchain)
		: mix::SwapchainBound(swapchain)
		, m_RenderPass(nullptr)
		, m_SwapchainSubscription(m_Swapchain.register_observer(this))
		, m_Data{}
	{
		_recreate_render_pass(*configuration, swapchain, device);
	}

	RenderPass::operator vk::RenderPass() const
	{
		return *m_RenderPass;
	}

	void RenderPass::recreate_framebuffers(Device& device)
	{
		m_Data.images = m_Swapchain.create_images();
		m_Data.views = convert<Vector<ImageView>>(m_Data.images, [&device](const auto& image) {
			return ImageView(device, *image);
		});

		m_Data.framebuffers = convert<Vector<Framebuffer>>(m_Data.views,
														   [this, &device](const auto& view) {
															   return Framebuffer(device,
																				  *this,
																				  view);
														   });
	}

	const Framebuffer& RenderPass::framebuffer_at(u32 index) const
	{
		return m_Data.framebuffers[index];
	}

	void RenderPass::on_swapchain_resized(SwapchainKHR& swapchain)
	{
		recreate_framebuffers(swapchain.burst_device());
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

		m_Data.dependencies.push_back(vk::SubpassDependency{
			/** src_subpass = */ 0u,
			/** dst_subpass = */ VK_SUBPASS_EXTERNAL,
			/** src_stage_flags  */
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			/** dst_stage_flags = */
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			/** src_access_flags = */ vk::AccessFlags(),
			/** dst_access_flags = */ vk::AccessFlagBits::eColorAttachmentWrite,
			/** flags = */ vk::DependencyFlags(),
		});


		auto subpasses = convert<Vector<SubpassDescription>>(m_Data.subpasses,
															 default_convertor<burst::vulkan::Subpass,
																			   SubpassDescription>);
		RenderPassCreateInfo create_info{
			RenderPassCreateFlags(), m_Data.descriptions, subpasses, m_Data.dependencies
		};

		m_RenderPass = raii::RenderPass(static_cast<raii::Device&>(device), create_info);
	}
}
