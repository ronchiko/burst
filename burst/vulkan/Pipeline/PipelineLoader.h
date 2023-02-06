#pragma once

#include "Pipeline.h"

namespace burst::vulkan {

	/**
	 * Helper class for loading a pipeline.
	 */
	class PipelineLoader
	{
	public:
		/**
		 * The pipeline loader class.
		 *
		 * \param device: The device to use for the pipeline creation
		 * \param swapchain: The device swapchain
		 * \param configuration: The configuration to use for the pipeline
		 */
		explicit PipelineLoader(burst::vulkan::Device& device,
								burst::vulkan::SwapchainKHR& swapchain,
								const Configuration& configuration);

		/**
		 * Constructs the actual pipeline.
		 */
		Pipeline create();

	private:
		/**
		 * Loads the shaders from the configuration.
		 */
		Vector<vk::PipelineShaderStageCreateInfo> _load_shaders();

		/**
		 * Creates the dynamic states info about the pipeline.
		 */
		vk::PipelineDynamicStateCreateInfo _create_dynamic_states();

		/**
		 * Creates a new vertex input state.
		 */
		vk::PipelineVertexInputStateCreateInfo _create_vertex_input_state();

		/**
		 * Creates the input assembly state.
		 */
		vk::PipelineInputAssemblyStateCreateInfo _create_input_assembly_state();

		/**
		 * Creates the viewport state.
		 */
		vk::PipelineViewportStateCreateInfo _create_viewport_state();

		/**
		 * Creates the rasteraziation state.
		 */
		vk::PipelineRasterizationStateCreateInfo _create_rasterization_state();

		/**
		 * Creates the multisample state.
		 */
		vk::PipelineMultisampleStateCreateInfo _create_multisample_state();

		/**
		 * Creates the color blend state.
		 */
		vk::PipelineColorBlendStateCreateInfo _create_color_blend_state();

		burst::vulkan::Device& m_Device;
		burst::vulkan::SwapchainKHR& m_Swapchain;
		const burst::vulkan::Configuration& m_Configuration;

		Pipeline::Data m_Data;
	};
}
