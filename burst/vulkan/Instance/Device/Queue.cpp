#include "Queue.h"

#include <burst/common/Log.h>

#include "burst/vulkan/Vk.h"

#include "Commands/CommandBuffer.h"
#include "Instance/SwapchainKHR/SwapchainKHR.h"

#include "Sync/Fence.h"
#include "Sync/Semaphore.h"


#define ARRAY_OF_1(name, element)                                                                  \
	::burst::Array<decltype(element), 1> name                                                      \
	{                                                                                              \
		(element)                                                                                  \
	}

namespace burst::vulkan {
	Queue::Queue(vk::Queue queue)
		: m_Submission()
		, m_Queue(queue)
	{}

	void Queue::push_stage(const Semaphore& wait_for, vk::PipelineStageFlags stage)
	{
		m_Submission.enqueue(static_cast<vk::Semaphore>(wait_for), stage);
	}

	void Queue::sumbit(CommandBuffer& buffer, const Semaphore& signal, const Fence& fence)
	{
		ARRAY_OF_1(buffers, static_cast<vk::CommandBuffer>(buffer));
		ARRAY_OF_1(signals, static_cast<vk::Semaphore>(signal));

		vk::SubmitInfo submission{
			m_Submission.semaphores,
			m_Submission.stages,
			buffers,
			signals,
		};

		m_Queue.submit({ submission }, static_cast<vk::Fence>(fence));
		m_Submission.flush();
	}

	void Queue::present(const Semaphore& wait_on, SwapchainKHR& swapchain, u32 index)
	{
		ARRAY_OF_1(wait_on_semaphores, static_cast<vk::Semaphore>(wait_on));
		ARRAY_OF_1(swapchains, static_cast<vk::SwapchainKHR>(swapchain));
		ARRAY_OF_1(indecies, index);

		VkPresentInfoKHR present_info = vk::PresentInfoKHR{ wait_on_semaphores, swapchains, indecies };

		const auto result = VK_CALL(vkQueuePresentKHR(static_cast<vk::Queue>(m_Queue), &present_info));

		// If we have one of these error codes, we need to recreate our swapchain
		if(result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR) {
			swapchain.force_recreation();
			return;
		}

		ASSERT(vk::Result::eSuccess == result, "Failed to present KHR");
	}
}
