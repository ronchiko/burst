#include "Renderer.h"

#include "Errors.h"

#include "Gpu.inl"
#include "Device.inl"

namespace burst::vulkan {

	/**
	 * Creates a surface KHR if its enabled.
	 *
	 * \param instance: The instance the surface is bound to
	 * \param configuration: The renderer configuration
	 * \param window: The window the surface is bound to
	 */
	static Optional<SurfaceKHR> create_surface_khr(
		Instance& instance, const Configuration& configuration, IWindow& window)
	{
		if(!configuration.instance.create_surface) {
			return std::nullopt;
		}

		return SurfaceKHR::create(instance, window);
	}

	Renderer::Context::ImageQueue::ImageQueue(Device& device,
		Address<SwapchainKHR> swapchain, Pipeline& pipeline)
	{
		if (!swapchain.is_ok()) {
			throw RuntimeError::make(
				"Cant create image queue because there is no surface");
		}

		swapchain_images = swapchain->create_images();
		image_views = convert<ImageView, Unique<IImage>>(
			swapchain_images, [&device](Unique<IImage>& image) {
				return ImageView(device, *image);
			});
		framebuffers =
			pipeline.render_pass().create_framebuffers(device, image_views);
	}

	Renderer::Context::Context(const ApplicationInfo& app,
							   const Configuration& configuration,
							   IVulkanWindow& window)
		: instance(app, configuration, window)
		, surface(create_surface_khr(instance, configuration, window))
		, gpu(find_suitable_gpu(instance, configuration))
		, queues(create_gpu_queues_object(gpu, configuration, surface))
		, device(gpu, queues, configuration)
		, swapchain(create_swapchain_khr(device, gpu, surface, window, queues, configuration))
		, pipeline(Pipeline::create(device, *swapchain, configuration))
		, image_queue(device, GET_ADDRESS(swapchain), pipeline)
		, pool(create_graphics_command_pool(device, queues))
		, command_buffer(device, pool)
	{}

	Renderer::Renderer(const ApplicationInfo& app,
					   const Configuration& configuration,
					   IVulkanWindow& window)
		: m_Context(app, configuration, window)
	{}

	void Renderer::render() {
		// For now, do nothing
	}
}
