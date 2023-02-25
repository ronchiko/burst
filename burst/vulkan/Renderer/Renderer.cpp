#include "Renderer.h"

#include "Errors.h"

#include "Device.inl"
#include "Gpu.inl"

#include "Commands/CommandRecorder.h"
#include "Pipeline/RenderPass/RenderPassContext.h"

namespace burst::vulkan {

	struct FrameContext
	{
		Pipeline& pipeline;
		SwapchainKHR& swapchain;
	};

	static void draw_frame(vk::CommandBuffer buffer, void *context)
	{
		FrameContext& ctx = *static_cast<FrameContext *>(context);

		Array<vk::Viewport, 1> viewports{
			vk::Viewport{ 0,
						  0,
						  static_cast<f32>(ctx.swapchain.width()),
						  static_cast<f32>(ctx.swapchain.height()),
						  0,
						  1 },
		};
		Array<vk::Rect2D, 1> scissors{
			vk::Rect2D{
				{ 0, 0 },
				{ ctx.swapchain.width(), ctx.swapchain.height() },
			},
		};

		buffer.bindPipeline(vk::PipelineBindPoint::eGraphics,
							static_cast<vk::Pipeline>(ctx.pipeline));

		buffer.setViewport(0, viewports);
		buffer.setScissor(0, scissors);

		buffer.draw(3, 1, 0, 0);
	}

	/**
	 * Creates a surface KHR if its enabled.
	 *
	 * \param instance: The instance the surface is bound to
	 * \param configuration: The renderer configuration
	 * \param window: The window the surface is bound to
	 */
	static Optional<SurfaceKHR> create_surface_khr(Instance& instance,
												   const Configuration& configuration,
												   IWindow& window)
	{
		if(!configuration.instance.create_surface) {
			return std::nullopt;
		}

		return SurfaceKHR::create(instance, window);
	}

	Renderer::Context::Context(const ApplicationInfo& app,
							   Shared<Configuration> configuration,
							   IVulkanWindow& window)
		: instance(app, configuration, window)
		, surface(create_surface_khr(instance, *configuration, window))
		, gpu(find_suitable_gpu(instance, *configuration))
		, queues(create_gpu_queues_object(gpu, *configuration, surface))
		, device(gpu, queues, configuration)
		, swapchain(create_swapchain_khr(device, gpu, surface, window, queues, configuration))
		, pipeline(Pipeline::create(device, *swapchain, configuration))
		, pool(create_graphics_command_pool(device, queues))
	{
		pipeline.render_pass().recreate_framebuffers(device);
	}

	Renderer::Renderer(const ApplicationInfo& app,
					   Shared<Configuration> configuration,
					   IVulkanWindow& window)
		: m_Context(app, configuration, window)
		, m_Drawers({
			  FrameDrawer(m_Context.device, m_Context.pool),
			  FrameDrawer(m_Context.device, m_Context.pool),

		  })
		, m_CurrentDrawer(0)
	{}

	Renderer::~Renderer()
	{
		try {
			static_cast<vk::Device>(m_Context.device).waitIdle();
		} catch(...) {}
	}

	void Renderer::render()
	{
		if(!m_Context.surface.has_value() || nullptr == m_Context.swapchain) {
			log::error("Trying to render on a non renderering surface");
			return;
		}

		FrameContext draw_frame_context{ m_Context.pipeline, *m_Context.swapchain };

		m_Drawers[m_CurrentDrawer].draw(m_Context.device,
										*m_Context.swapchain,
										m_Context.pipeline.render_pass(),
										&draw_frame,
										&draw_frame_context);

		m_CurrentDrawer = (m_CurrentDrawer + 1) % m_Drawers.size();
	}
}
