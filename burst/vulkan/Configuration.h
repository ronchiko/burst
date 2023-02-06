#pragma once

#include <burst/Common.h>

#include "Instance/Gpu/IGpuAnalyzer.h"
#include "Instance/Requirement.h"

#include "Instance/SwapchainKHR/Usage.h"

namespace burst::vulkan {

	constexpr f32 DEFAULT_LINE_WIDTH = 1.F;

	class IShaderLoader;
	class IDynamicStateHandler;

	/**
	 * The vulkan configuration.
	 */
	struct Configuration
	{
		// The dependencies
		Vector<Requirement> requirements = {};

		struct Instance
		{
			// Should the instance attach a surface
			bool create_surface = true;
		};

		struct Gpu
		{
			// The gpu queue locator
			Vector<IQueueLocator *> locators;
			// The analyzer to use to select the target GPU
			IGpuAnalyzer *analyzer = nullptr;
		};

		struct Swapchain
		{
			// The image usage type for the swapchain
			UnionEnum<ImageUsage, vk::ImageUsageFlagBits> usage =
				ImageUsage::AttachColor;
			// The composite alpha type for the swapchain
			UnionEnum<CompositeAlpha, vk::CompositeAlphaFlagBitsKHR> composite =
				CompositeAlpha::Opaque;
		};

		struct Pipeline
		{
			struct Rasterizer
			{
				vk::PolygonMode polygon_mode = vk::PolygonMode::eFill;
				vk::CullModeFlags cull_mode = vk::CullModeFlagBits::eBack;
				vk::FrontFace frontface = vk::FrontFace::eClockwise;

				f32 line_width = DEFAULT_LINE_WIDTH;
			} rasterizer;

			struct Multisample
			{
				vk::SampleCountFlagBits sample_count = vk::SampleCountFlagBits::e1;
				bool sample_shading = false;
				f32 min_sample_shading = 0.F;
			} multisample;

			struct Blend
			{
				vk::BlendFactor source_factor = vk::BlendFactor::eOne;
				vk::BlendFactor destination_factor = vk::BlendFactor::eZero;
				vk::BlendOp operation = vk::BlendOp::eAdd;
			};

			struct ColorAttachment
			{
				bool enable_blend = true;
				Blend color_blend = { vk::BlendFactor::eSrcAlpha,
									  vk::BlendFactor::eOneMinusSrcAlpha,
									  vk::BlendOp::eAdd };
				Blend alpha_blend = { vk::BlendFactor::eOne,
									  vk::BlendFactor::eZero,
									  vk::BlendOp::eAdd };
				u32 channels = static_cast<u32>(
					vk::FlagTraits<vk::ColorComponentFlagBits>::allFlags);
			};

			// The shaders used by the pipeline
			Vector<IShaderLoader *> shaders;
			// The dynamic state handler for the pipeline
			Vector<IDynamicStateHandler *> dynamic_states;
			// The topology for rendering
			vk::PrimitiveTopology topology = vk::PrimitiveTopology::eTriangleList;
			// Color attachments
			Vector<ColorAttachment> color_attachments;
		};

		Instance instance = {};
		Gpu gpu = {};
		Swapchain swapchain = {};
		Pipeline pipeline = {};

		static Configuration create_default_configuration();
	};
}
