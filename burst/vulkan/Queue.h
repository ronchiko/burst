#pragma once

#include <vulkan/vulkan.h>

namespace burst::vulkan {
	class Queue {
	public:
		explicit Queue(VkQueue queue);

	private:
		VkQueue m_Queue;
	};

}
