#pragma once

#include <vulkan/vulkan_raii.hpp>


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

	private:
		vk::raii::Semaphore m_Semaphore;
	};
}