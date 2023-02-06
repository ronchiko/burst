#pragma once


#include "../IQueueLocator.h"

namespace burst::vulkan {

	/**
	 * A queue locator that locates the graphics queue for a gpu.
	 */
	class GraphicsQueueLocator : public IQueueLocator
	{
	public:
		/**
		 * Locates the target queue.
		 */
		virtual Status locate(const QueueFamilyProperties& properties, Queues& queue) override;
	};
}


