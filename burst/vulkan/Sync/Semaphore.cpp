#include "Semaphore.h"

#include <burst/common/Log.h>

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
		: m_Device(device)
		, m_Semaphore(create_semaphore(device))
	{}

	Semaphore::operator vk::Semaphore() const
	{
		return *m_Semaphore;
	}

	void Semaphore::wait(u64 timeout) const
	{
		Vector<vk::Semaphore> semaphores{ *m_Semaphore };
		Vector<u64> values{ 0 };
		vk::SemaphoreWaitInfo wait_info{
			vk::SemaphoreWaitFlags(),
			semaphores,
			values
		};

		CHECK(
			vk::Result::eSuccess ==
				static_cast<vk::Device>(m_Device).waitSemaphores(wait_info, timeout),
			"Failed to wait for semaphores");
	}
}
