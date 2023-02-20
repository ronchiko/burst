#pragma once

#include <vulkan/vulkan_raii.hpp>

#include <burst/common/Types.h>

namespace burst::vulkan {
	class Device;

	/**
	 * Vulkan GPU semaphore RAII wrapper.
	 */
	class Semaphore final
	{
	public:
		Semaphore(Device& device);

		operator vk::Semaphore() const;

		void wait(u64 timeout = UINT64_MAX) const;

	private:
		Device& m_Device;
		vk::raii::Semaphore m_Semaphore;
	};
}