#include "Queues.h"

#include <burst/common/Error.h>

namespace burst::vulkan {
	GpuQueue& GpuQueues::operator[](u32 index) {
		if (index >= MAX_QUEUES) {
			throw burst::StaticError("Queue index out of bounds");
		}

		return m_Queues[index];
	}

	GpuQueue& GpuQueues::operator[](QueueType type) {
		return (*this)[static_cast<u32>(type)];
	}
}
