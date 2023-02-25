#include "PipelineLoader.h"

#include "IDynamicStateHandler.h"
#include "Shaders/IShaderLoader.h"

#include "../Instance/Device/Device.h"
#include "../Instance/SwapchainKHR/SwapchainKHR.h"

using namespace vk;

constexpr ColorComponentFlags ALL_CHANNELS = ColorComponentFlagBits::eR |
											 ColorComponentFlagBits::eG |
											 ColorComponentFlagBits::eB |
											 ColorComponentFlagBits::eA;

namespace burst::vulkan {

	constexpr static Pair<Viewport, Rect2D> flat_viewport(const SwapchainKHR& swapchain)
	{
		return {
			Viewport{
				.0F,
				.0F,
				static_cast<f32>(swapchain.width()),
				static_cast<f32>(swapchain.height()),
				.0F,
				1.F,
			},
			Rect2D{
				{ 0, 0 },
				{ swapchain.width(), swapchain.height() },
			},
		};
	}

	PipelineLoader::PipelineLoader(burst::vulkan::Device& device,
								   burst::vulkan::SwapchainKHR& swapchain,
								   Shared<Configuration> config)
		: m_Device(device)
		, m_Swapchain(swapchain)
		, m_Configuration(config)
		, m_Data()
	{}

	Vector<PipelineShaderStageCreateInfo> PipelineLoader::_load_shaders()
	{
		Vector<PipelineShaderStageCreateInfo> loaded_shaders{};

		for(const IShaderLoader *shader_loader : m_Configuration->pipeline.shaders) {
			auto shader = shader_loader->load(m_Device);

			PipelineShaderStageCreateInfo
				shader_create_info(PipelineShaderStageCreateFlags(),
								   static_cast<ShaderStageFlagBits>(shader.type()),
								   static_cast<ShaderModule>(shader),
								   "main");

			loaded_shaders.push_back(shader_create_info);
			m_Data.owned_shaders.push_back(std::move(shader));
		}

		return loaded_shaders;
	}

	PipelineDynamicStateCreateInfo PipelineLoader::_create_dynamic_states()
	{
		Set<DynamicState> dynamic_states{};

		for(const auto& handler : m_Configuration->pipeline.dynamic_states) {
			auto states = handler->get_states();

			dynamic_states.insert(states.begin(), states.end());
		}

		auto unique_dynamic_states = iter_convert<Vector<DynamicState>>(dynamic_states);

		m_Data.dynamic_states = unique_dynamic_states;
		return PipelineDynamicStateCreateInfo(PipelineDynamicStateCreateFlags(),
											  m_Data.dynamic_states);
	}

	PipelineVertexInputStateCreateInfo PipelineLoader::_create_vertex_input_state()
	{
		// TODO: Think of a mechanism to get the attributes & bindings from the
		// shaders
		m_Data.vertex_attributes = {};
		m_Data.vertex_bindings = {};

		return PipelineVertexInputStateCreateInfo(PipelineVertexInputStateCreateFlags(),
												  m_Data.vertex_bindings,
												  m_Data.vertex_attributes);
	}

	PipelineInputAssemblyStateCreateInfo PipelineLoader::_create_input_assembly_state()
	{
		return PipelineInputAssemblyStateCreateInfo(PipelineInputAssemblyStateCreateFlags(),
													m_Configuration->pipeline.topology,
													false);
	}

	PipelineViewportStateCreateInfo PipelineLoader::_create_viewport_state()
	{
		auto [viewport, scissor] = flat_viewport(m_Swapchain);

		m_Data.viewports = { viewport };
		m_Data.scissors = { scissor };

		return PipelineViewportStateCreateInfo(PipelineViewportStateCreateFlagBits(),
											   m_Data.viewports,
											   m_Data.scissors);
	}

	PipelineRasterizationStateCreateInfo PipelineLoader::_create_rasterization_state()
	{
		return PipelineRasterizationStateCreateInfo(PipelineRasterizationStateCreateFlags(),
													/** depth_clamp_enable = */ false,
													/** rasterizer_discard_enable = */ false,
													m_Configuration->pipeline.rasterizer.polygon_mode,
													m_Configuration->pipeline.rasterizer.cull_mode,
													m_Configuration->pipeline.rasterizer.frontface,
													/** depth_bias_enable = */ false,
													/** depth_bias_constant_factor = */ 0.F,
													/** depth_bias_clamp = */ 0.F,
													/** depth_bias_slope_factor = */ 0.F,
													m_Configuration->pipeline.rasterizer.line_width);
	}

	PipelineMultisampleStateCreateInfo PipelineLoader::_create_multisample_state()
	{
		return PipelineMultisampleStateCreateInfo(PipelineMultisampleStateCreateFlags(),
												  m_Configuration->pipeline.multisample.sample_count,
												  m_Configuration->pipeline.multisample.sample_shading,
												  m_Configuration->pipeline.multisample
													  .min_sample_shading,
												  /** sample_mask = */ nullptr,
												  /** alpha_to_coverage_enable = */ false,
												  /** alpha_to_one_enable = */ false);
	}

	PipelineColorBlendStateCreateInfo PipelineLoader::_create_color_blend_state()
	{
		// Create attachment using configuration
		Vector<PipelineColorBlendAttachmentState> attachments{};
		attachments.reserve(m_Configuration->pipeline.color_attachments.size());

		for(const auto& attachment : m_Configuration->pipeline.color_attachments) {
			attachments.push_back(PipelineColorBlendAttachmentState{
				attachment.enable_blend,
				attachment.color_blend.source_factor,
				attachment.color_blend.destination_factor,
				attachment.color_blend.operation,
				attachment.alpha_blend.source_factor,
				attachment.alpha_blend.destination_factor,
				attachment.alpha_blend.operation,
				static_cast<vk::ColorComponentFlags>(attachment.channels),
			});
		}

		m_Data.color_blend_attachments = attachments;
		return PipelineColorBlendStateCreateInfo(PipelineColorBlendStateCreateFlags(),
												 /** enable_logic_operation = */ false,
												 /** logic_operation = */ LogicOp::eCopy,
												 m_Data.color_blend_attachments,
												 /** blend_constants = */ Array<f32, 4>());
	}

	Pipeline PipelineLoader::create()
	{
		auto shaders = _load_shaders();
		auto dynamic_states = _create_dynamic_states();
		auto vertex_input = _create_vertex_input_state();
		auto input_assembly = _create_input_assembly_state();
		auto viewport_state = _create_viewport_state();
		auto rasterization_state = _create_rasterization_state();
		auto multisample_state = _create_multisample_state();
		auto color_blend_state = _create_color_blend_state();

		auto render_pass = std::make_unique<burst::vulkan::RenderPass>(m_Configuration,
																	   m_Device,
																	   m_Swapchain);

		Vector<DescriptorSetLayout> sets_layouts{};
		Vector<PushConstantRange> push_constants{};

		vk::PipelineLayoutCreateInfo layout_create_info{
			vk::PipelineLayoutCreateFlags(),
			sets_layouts,
			push_constants,
		};

		auto layout = static_cast<vk::raii::Device&>(m_Device)
						  .createPipelineLayout(layout_create_info);

		GraphicsPipelineCreateInfo create_info{ PipelineCreateFlags(),
												shaders,
												&vertex_input,
												&input_assembly,
												nullptr,
												&viewport_state,
												&rasterization_state,
												&multisample_state,
												nullptr,
												&color_blend_state,
												&dynamic_states,
												*layout,
												static_cast<vk::RenderPass>(*render_pass),
												/** subpass = */ 0,
												/** pipeline_handle = */ VK_NULL_HANDLE,
												/** pipeline_index = */ -1 };

		// Recreate the render pass before framebuffer we pass it to the pipeline
		render_pass->recreate_framebuffers(m_Device);

		return Pipeline{
			vk::raii::Pipeline(static_cast<vk::raii::Device&>(m_Device), VK_NULL_HANDLE, create_info),
			std::move(render_pass),
			std::move(layout),
			std::move(m_Data),
		};
	}
}