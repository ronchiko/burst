#pragma once

#include <optional>

#include <burst/common/Types.h>

namespace burst::vulkan {
	
	using GpuQueue = std::optional<u32>;

	ENUM QueueType{
		Graphics = 0,
		Present = 1
	};

	struct GpuQueues {
		static constexpr u32 MAX_QUEUES = 64;

		constexpr GpuQueue operator[](u32 index) const {
			return index >= MAX_QUEUES ? GpuQueue{} : m_Queues[index];
		}

		constexpr GpuQueue operator[](QueueType type) const {
			return (*this)[static_cast<u32>(type)];
		}

		GpuQueue& operator[](u32 index);
		GpuQueue& operator[](QueueType type);

	private:
		GpuQueue m_Queues[MAX_QUEUES];
	};
}
