#pragma once

#include <Burst/Common/IRenderer.h>

#include "Configuration.h"
#include "Instance/Instance.h"
#include "Instance/Gpu/Gpu.h"
#include "Instance/Device/Device.h"
#include "Instance/SurfaceKHR/SurfaceKHR.h"
#include "Instance/SwapchainKHR/SwapchainKHR.h"

#include "Pipeline/Pipeline.h"

#include "Commands/CommandPool.h"
#include "Commands/CommandBuffer.h"

#include "IVulkanWindow.h"

namespace burst::vulkan {
	/**
	 * Creates a new renderer.
	 */
	class Renderer : public IRenderer
	{
	public:
		/**
		 * Creates a new vulkan renderer.
		 *
		 * \param configuration: The configuration to use
		 */
		explicit Renderer(const ApplicationInfo& app,
						  const Configuration& configuration,
						  IVulkanWindow& window);

		/**
		 * Renders :)
		 */
		virtual void render() override;

	private:
		// The vulkan context of the render
		// Contains all the critial structures for this instance
		struct Context
		{
			Instance instance;
			Optional<SurfaceKHR> surface;
			
			Gpu gpu;
			Queues queues;

			Device device;

			Optional<SwapchainKHR> swapchain;

			Pipeline pipeline;

			struct ImageQueue
			{
				Vector<Unique<IImage>> swapchain_images;
				Vector<ImageView> image_views;
				Vector<vk::raii::Framebuffer> framebuffers;

				ImageQueue(Device&, Address<SwapchainKHR>, Pipeline&);
			} image_queue;

			CommandPool pool;
			CommandBuffer command_buffer;

			
			explicit Context(const ApplicationInfo& app,
							 const Configuration& configuration,
							 IVulkanWindow& window);
			
		} m_Context; 

	};
}
