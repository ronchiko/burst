#include "GraphicsQueueLocator.h"

#include "../../SurfaceKHR/GpuSurface.h"

namespace burst::vulkan {
	GraphicsQueueLocator::Status
	GraphicsQueueLocator::locate(const QueueFamilyProperties& properties,
								 Queues& queues)
	{
		if(properties.queueFlags & vk::QueueFlagBits::eGraphics) {
			queues[QueueType::Graphics] = properties.index;

			if(properties.surface.is_ok()) {
				GpuSurfaceBinding surface(*properties.surface,
										  properties.gpu.get());

				if(surface.does_surface_support_khr(properties.index)) {
					queues[QueueType::Present] = properties.index;
				}
			}

			return Status::Success;
		}

		return Status::Failure;
	}
}
