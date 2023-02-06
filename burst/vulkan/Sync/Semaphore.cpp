#include "Semaphore.h"

#include "../Instance/Device/Device.h"

#include "Errors.h"

constexpr VkSemaphoreCreateInfo SEMAPHORE_CREATE_INFO = {
	VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
};

namespace burst::vulkan {
	/**
	 * Creates a new vulkan GPU semaphore.
	 */
	static vk::raii::Semaphore create_semaphore(Device& device)
	{
		return vk::raii::Semaphore(static_cast<vk::raii::Device&>(device),
								   SEMAPHORE_CREATE_INFO);
	}

	Semaphore::Semaphore(Device& device)
		: m_Semaphore(create_semaphore(device))
	{}

	Semaphore::operator vk::Semaphore() const
	{
		return *m_Semaphore;
	}
}
