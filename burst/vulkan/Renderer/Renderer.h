#pragma once

#include <Burst/Common/IRenderer.h>

#include "../Configuration.h"
#include "../Instance/Instance.h"
#include "../Instance/Gpu/Gpu.h"
#include "../Instance/Device/Device.h"
#include "../Instance/SurfaceKHR/SurfaceKHR.h"
#include "../Instance/SwapchainKHR/SwapchainKHR.h"

#include "../Pipeline/Pipeline.h"

#include "../Commands/CommandPool.h"

#include "FrameDrawer.h"

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
						  Shared<Configuration> configuration,
						  IVulkanWindow& window);

		// We override destructor to wait before release the resources
		virtual ~Renderer() override;

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

			Unique<SwapchainKHR> swapchain;

			Pipeline pipeline;

			CommandPool pool;

			explicit Context(const ApplicationInfo& app,
							 Shared<Configuration> configuration,
							 IVulkanWindow& window);
			
		} m_Context; 

		Array<FrameDrawer, 2> m_Drawers;
		u32 m_CurrentDrawer;
	};
}
