#pragma once

#include "../Instance/Device/Device.h"
#include "../Instance/SurfaceKHR/GpuSurface.h"
#include "../Instance/SwapchainKHR/SwapchainKHR.h"

#include "../Commands/CommandPool.h"

namespace burst::vulkan {

	/**
	 * Creates a new SwapchainKHR object if possible .
	 * \see SwapchainKHR::create
	 */
	inline Optional<SwapchainKHR> create_swapchain_khr(Device& device,
									   Gpu& gpu,
									   Optional<SurfaceKHR>& surface,
									   IWindow& window,
									   Queues& queues,
									   const Configuration& config)
	{
		if (!surface.has_value()) {
			return std::nullopt;
		}

		GpuSurfaceBinding binding(surface.value(), gpu);
		return SwapchainKHR::create(device, binding, window, queues, config);
	}

	/**
	 * Creates a new graphics command pool.
	 * 
	 * \param device: The device to create the pool into
	 * \param queues: The gpu queues of the device
	 * 
	 * \throw FailedToCreateCommandPoolError: When there isn't QueueType::Graphics in queues
	 * \return The new command pool
	 */
	inline CommandPool create_graphics_command_pool(Device& device, Queues& queues)
	{
		if (!queues.has_queue(QueueType::Graphics)) {
			throw FailedToCreateCommandPoolError("No graphics queue for device");
		}

		return CommandPool(device, queues[QueueType::Graphics].value());
	}

}
