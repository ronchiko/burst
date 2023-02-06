#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "../Configuration.h"
#include "Shaders/Shader.h"

#include "RenderPass/RenderPass.h"

namespace burst::vulkan {
	class Device;
	class SwapchainKHR;
	class PipelineLoader;

	class Pipeline
	{
	public:
		/**
		 * Creates a new pipeline.
		 *
		 * \param device: The device to create the pipeline to
		 * \param swapchain: The swapchain the pipeline is bound to
		 * \param configuration: The configuration the pipeline should use
		 */
		static Pipeline create(Device& device,
							   SwapchainKHR& swapchain,
							   const Configuration& configuration);

		/**
		 * The render pass of this pipline.
		 */
		const RenderPass& render_pass() const;

	private:
		friend class burst::vulkan::PipelineLoader;

		struct Data
		{
			Vector<Shader> owned_shaders;

			Vector<vk::VertexInputBindingDescription> vertex_bindings;
			Vector<vk::VertexInputAttributeDescription> vertex_attributes;

			Vector<vk::Viewport> viewports;
			Vector<vk::Rect2D> scissors;

			Vector<vk::PipelineColorBlendAttachmentState> color_blend_attachments;
			Vector<vk::DynamicState> dynamic_states;
		};

		explicit Pipeline(vk::raii::Pipeline pipeline,
						  RenderPass render_pass,
						  vk::raii::PipelineLayout layout,
						  Data data);

		vk::raii::Pipeline m_Pipeline;
		RenderPass m_RenderPass;
		vk::raii::PipelineLayout m_Layout;
		Data m_Data;
	};
}
